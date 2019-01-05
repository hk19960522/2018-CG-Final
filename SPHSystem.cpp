#include "SPHSystem.h"
#include <cmath>

#define PI 3.1415926

SPHSystem::SPHSystem(SceneManager *mgr)
{
	// r = 100 unit
	sceneMgr = mgr;
	time = 0;

	h = DATA_READER::getSmoothSize();
	m = 1.0;
	poly6 = m * 315.0 / ( 64.0 * PI * pow(h, 9.0f) );
	spiky = m * 45.0 / ( PI * pow(h, 6.0f) );
	pressureCoef = DATA_READER::getPressureCoef();
	initDensity = DATA_READER::getInitDensity();
	viscosityCoef = 0.018;

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
	UpdateDensity();
	UpdateAcceleration();
	for (int i=0;i<particles.size();++i) {
		particles[i]->Update(0.01);
	}
	time += evt.timeSinceLastFrame;
	if(time > 0.1){
		float particleRadius = DATA_READER::getParticleRadius();
		//cout << "----------------------------------123particle radius = " << particleRadius <<endl;
		createParticle(1, particleRadius, Vector3::ZERO);
		time = 0;
	}
}

void SPHSystem::UpdateDensity()
{
	int size = particles.size();
	for (int i=0;i<size;++i) {
		SPHParticle *p0 = particles[i];
		float density = 0.0f;

		for (int j=0;j<size;j++) {
			if (i == j) continue;
			SPHParticle *p1 = particles[j];

			const Vector3& direction = p0->GetPosition() - p1->GetPosition();
			if (direction.squaredLength() > h * h) {
				continue;
			}

			float diff = h * h - direction.squaredLength();
			density += poly6 * diff * diff * diff;
		}
		//std::cout << "den : " << density << " --- ";

		p0->SetDensity(density);
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


		for (int j=0;j<size;++j) {
			if (i == j) continue;
			SPHParticle *p1 = particles[j];
			Vector3 direction = p0->GetPosition() - p1->GetPosition();
			float dist = direction.length();

			if (dist == 0.0 || dist > h) continue;

			direction = direction * ( 1.0 / dist );
			// pressure
			float ratio = (p0->pressure + p1->pressure) / ( 2 * p0->density * p1->density );
			float diff = h - dist;
			acc += ( spiky * ratio * diff * diff ) * direction;
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