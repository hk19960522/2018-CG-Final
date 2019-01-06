#include "SPHSystem.h"
#include <cmath>
#include <map>

#define PI 3.1415926

SPHSystem::SPHSystem(SceneManager *mgr)
{
	// r = 100 unit
	sceneMgr = mgr;
	time = 0;

	h = DATA_READER::getSmoothSize();
	m = DATA_READER::getParticleMass();
	poly6 = m * 315.0 / ( 64.0 * PI * pow(h, 9.0f) );
	spiky = m * 45.0 / ( PI * pow(h, 6.0f) );
	pressureCoef = DATA_READER::getPressureCoef();
	initDensity = DATA_READER::getInitDensity();
	viscosityCoef = DATA_READER::getViscosityCoef();
	visKernel = m * viscosityCoef * 45.0 / (PI * pow(h, 6.0f));
	boundDampingCoef = DATA_READER::getBoundDampingCoef();
	BuildCubeParticle(10);

	xMin = yMin = zMin = 0.0;
	xMax = DATA_READER::getBoundX();
	zMax = DATA_READER::getBoundZ();
}

void SPHSystem::BuildCubeParticle(int size, float offset)
{
	Vector3 center(DATA_READER::getBoundX() * 0.5f, 10.0, DATA_READER::getBoundZ() * 0.5f);
	center -= Vector3((float)size * h + h, 0, (float)size * h + h);
	float scale = 0.9f;
	for (int x=0;x<size;++x) {
		for (int y=0;y<size;++y) {
			for (int z=0;z<size;++z) {
				Vector3 pos = center + Vector3(offset * h * (float)x, offset * h * (float)y, offset * h * (float)z);
				//std::cout << pos << std::endl;
				createParticle(pos, DATA_READER::getParticleRadius());
			}
		}
	}
}

void SPHSystem::createParticle(Vector3 pos, float r){
	Entity *ent = sceneMgr->createEntity("sphere.mesh");
	ent -> setMaterialName("Examples/blue");
	SceneNode *snode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(ent);

	snode->setPosition(pos);

	SPHParticle *particle = new SPHParticle(snode, 1, 1, Vector3::ZERO, initDensity);
	particles.push_back(particle);
	float scaleSize = r/100.0f;
	snode->scale(scaleSize, scaleSize, scaleSize);
}

void SPHSystem::createParticle(float m, float r, Vector3 v){
	Entity *ent = sceneMgr->createEntity("sphere.mesh");
	SceneNode *snode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(ent);

	snode->setPosition(Vector3((rand()%20 - 10) / 10.0,10,(rand()%20 - 10)/10.0));

	SPHParticle *particle = new SPHParticle(snode, 1, 1, Vector3::ZERO, initDensity);
	particles.push_back(particle);
	float scaleSize = r/100.0f;
	snode->scale(scaleSize, scaleSize, scaleSize);
}

void SPHSystem::Update(const Ogre::FrameEvent& evt)
{
	BuildParticleNeighbor();
	UpdateDensity();
	UpdateAcceleration();
	for (int i=0;i<particles.size();++i) {
		particles[i]->Update(0.005);
		UpdateBoundaryInfo(particles[i]);
	}
	//system("PAUSE");
	time += evt.timeSinceLastFrame;
	//if(time > 5.0){
	//	float particleRadius = DATA_READER::getParticleRadius();
	//	//cout << "----------------------------------123particle radius = " << particleRadius <<endl;
	//	BuildCubeParticle(10);
	//	time = 0;
	//}
}

void SPHSystem::BuildParticleNeighbor()
{
	std::map<long long, std::vector<int> > m;

	int size = particles.size();
	Vector3 pos;
	for (int i=0;i<size;++i) {
		particles[i]->neighbor.clear();
		pos = particles[i]->GetPosition();
		
		int x = floor(pos.x / h), y = floor(pos.y / h), z = floor(pos.z / h);
		long long hash = x * 1000000 + y * 1000 + z;

		//std::cout << pos << " " << x << " " << y << " " << z << std::endl;
		m[hash].push_back(i);
		//std::cout << m[hash].size() << std::endl;
	}

	for (int i=0;i<size;++i) {
		particles[i]->neighbor.clear();
		pos = particles[i]->GetPosition();
		
		int x = floor(pos.x / h), y = floor(pos.y / h), z = floor(pos.z / h);
		long long hash = 0;
		for (int dx = -1; dx <= 1; ++dx) {
			if ((x + dx) < 0) continue;
			for (int dy = -1; dy <= 1; ++dy) {
				if ((y + dy) < 0) continue;
				for (int dz = -1; dz <= 1; ++dz) {
					if ((z + dz) < 0) continue;
					hash = (x + dx) * 1000000 + (y + dy) * 1000 + (z + dz);
					std::vector<int>& part = m[hash];
					//std::cout << part.size() << std::endl;

					for (int j=0;j<part.size();j++) {
						int index = part[j];
						if (i == index) continue;
						//std::cout << "p0 : " << particles[i]->GetPosition() << " p1 : " << particles[index]->GetPosition() << std::endl;
						//std::cout << "Sqdis : " << particles[i]->GetPosition().squaredDistance(particles[index]->GetPosition()) << std::endl;
						if (particles[i]->GetPosition().squaredDistance(particles[index]->GetPosition()) <= h * h) {
							particles[i]->neighbor.push_back(index);
						}
					}
				}
			}
		}
	}

	//for (int i=0;i<size;++i) {
	//	SPHParticle * p = particles[i];
	//	std::cout << "Particle " << i << " neighbor :\n";
	//	for (int j=0;j<p->neighbor.size();++j) {
	//		std::cout << p->neighbor[j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
}

void SPHSystem::UpdateDensity()
{
	int size = particles.size();
	for (int i=0;i<size;++i) {
		SPHParticle *p0 = particles[i];
		float density = 0.0f;

		for (int j=0;j<p0->neighbor.size();j++) {
			if (i == j) continue;
			SPHParticle *p1 = particles[p0->neighbor[j]];

			const Vector3& direction = p0->GetPosition() - p1->GetPosition();
			if (direction.squaredLength() > h * h) {
				continue;
			}

			float diff = h * h - direction.squaredLength();
			density += poly6 * diff * diff * diff;
		}
		//std::cout << "den : " << density << " --- ";

		p0->SetDensity(max(density, initDensity));
		p0->SetPressure(pressureCoef * (p0->Density() - initDensity));

		//std::cout << "den : " << p0->density << " --- ";
	}
	//std::cout << std::endl;
}

void SPHSystem::UpdateAcceleration()
{
	int size = particles.size();
	for (int i=0;i<size;++i) {
		SPHParticle *p0 = particles[i];
		Vector3 acc = Vector3::ZERO;


		for (int j=0;j<p0->neighbor.size();j++) {
			if (i == j) continue;
			SPHParticle *p1 = particles[p0->neighbor[j]];
			Vector3 direction = p0->GetPosition() - p1->GetPosition();
			float dist = direction.length();

			if (dist == 0.0 || dist > h) continue;

			direction = direction * ( 1.0 / dist );
			// pressure
			float ratio = (p0->pressure + p1->pressure) / ( 2 * p0->density * p1->density );
			float diff = h - dist;
			acc += ( spiky * ratio * diff * diff ) * direction;

			float vis = viscosityCoef * diff;
			Vector3 vdiff = p1->velocity - p0->velocity;
			acc += (visKernel * vis / (p0->density * p1->density) ) * vdiff;
		}
		//std::cout << acc << " ";
		// gravity

		acc += Vector3(0, -9.8, 0);

		float accLength = acc.length();
		if (accLength > 75.0) 
			acc = acc / accLength * 75.0;

		p0->acceleration = acc;
	}
	//std::cout << endl;
}

void SPHSystem::UpdateBoundaryInfo(SPHParticle *p)
{
	Vector3 pos = p->GetPosition();
	float eps = 0.001;
	float damp = boundDampingCoef;

	if (pos.x < 0.0) {
		pos.x = xMin + eps;
		p->velocity.x = -damp * p->velocity.x;
	}
	else if (pos.x > xMax) {
		pos.x = xMax - eps;
		p->velocity.x = -damp * p->velocity.x;
	}

	if (pos.y < 0.0) {
		pos.y = yMin + eps;
		p->velocity.y = -damp * p->velocity.y;
	}

	if (pos.z < 0.0) {
		pos.z = zMin + eps;
		p->velocity.z = -damp * p->velocity.z;
	}
	else if (pos.z > zMax) {
		pos.z = zMax - eps;
		p->velocity.z = -damp * p->velocity.z;
	}

	p->SetPosition(pos);
}