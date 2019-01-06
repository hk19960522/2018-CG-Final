#ifndef PARTICLE_H
#define PARTICLE_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include "BasicTools.h"
#include <vector>

using namespace Ogre;

class SPHParticle
{
public :
	SPHParticle(SceneNode *snode, float m, float r, Vector3 v, float d);

	void Update(float deltaT);
	const Vector3& GetPosition() { return sceneNode->getPosition(); };

	float Density() { return density; };

	void SetDensity(float d) { density = d; };
	void SetPressure(float p) { pressure = p; };
	void SetPosition(Vector3 p) { sceneNode->setPosition(p); };

	float density;
	float pressure;
	Vector3 velocity;  
	Vector3 acceleration;
	Vector3 halfVelocity;

	std::vector<int> neighbor;

private :
	SceneNode *sceneNode;
	float mass;
	float radius;
	
	void UpdatePosition(float deltaT);
	void BoundaryCheck();
};

#endif