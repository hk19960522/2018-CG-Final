#include "Particle.h"

SPHParticle::SPHParticle(SceneNode *snode, float m, float r, Vector3 v)
{
	sceneNode = snode;
	mass = m;
	radius = r;
	velocity = v;
}

void SPHParticle::Update(float deltaT)
{
	// Gravity
	Vector3 final = Vector3(0, -9.8, 0);

	sceneNode->translate(final * deltaT);
}