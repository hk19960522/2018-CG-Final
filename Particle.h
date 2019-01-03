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

using namespace Ogre;

class SPHParticle
{
public :
	SPHParticle(SceneNode *snode, float m, float r, Vector3 v);

	void Update(float deltaT);

private :
	SceneNode *sceneNode;
	float mass;
	float radius;
	Vector3 velocity;  

	
};

#endif