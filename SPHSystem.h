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
	void BuildCubeParticle(int size, float offset = 0.9);

private:
	SceneManager *sceneMgr;
	std::vector<SPHParticle *> particles;

	// Parameter
	float h; // kernel size
	float m; // mass of particle
	float poly6; // const of poly 6 kernel function
	float spiky; // const of spiky kernel function
	float visKernel;

	float pressureCoef; // K
	float viscosityCoef;
	float boundDampingCoef;

	float initDensity; // init density

	float xMin, xMax, yMin, zMin, zMax;

	
	void SPHSystem::createParticle(Vector3 pos, float r);
	void createParticle(float m, float r, Vector3 v); 

	void BuildParticleNeighbor();
	void UpdateDensity();
	void UpdateAcceleration();
	void UpdateBoundaryInfo(SPHParticle *p);

	float time;
	
};



#endif SPHSYSTEM_H