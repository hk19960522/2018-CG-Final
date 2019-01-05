#include "Particle.h"
SPHParticle::SPHParticle(SceneNode *snode, float m, float r, Vector3 v, float d)
{
	sceneNode = snode;
	mass = m;
	radius = r;
	velocity = v;
	density = d;
}


void SPHParticle::Update(float deltaT)
{
	// Gravity
	//sceneNode->translate(acceleration * deltaT * deltaT);
	UpdatePosition(deltaT);
	
	Vector3 p = sceneNode->getPosition();
	if (p.y < 0.0) p.y = 0;
	if (p.x < -2.0) p.x = -2;
	if (p.x > 2.0) p.x = 2;
	if (p.z < -2.0) p.z = -2;
	if (p.z > 2.0) p.z = 2;
	sceneNode->setPosition(p);
	
	
	
}

void SPHParticle::UpdatePosition(float deltaT)
{
	Vector3 nextVelo = velocity + acceleration * deltaT;
	Vector3 p = sceneNode->getPosition();

	p += nextVelo * deltaT;
	halfVelocity  = (velocity + nextVelo) * 0.5;
	velocity = nextVelo;
	sceneNode->setPosition(p);
}