#ifndef SPHSYSTEM_H
#define SPHSYSTEM_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <vector>
#include "Particle.h"
#include "read_data.h"

using namespace std;
using namespace Ogre;


class SPHSystem
{
public :
	SPHSystem(SceneManager *mgr);

	void Update(const Ogre::FrameEvent& evt);

private:
	SceneManager *sceneMgr;
	std::vector<SPHParticle *> particles;

	void createParticle(float m, float r, Vector3 v); 

	float time;
	
};



#endif SPHSYSTEM_H