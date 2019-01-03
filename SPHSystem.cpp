#include "SPHSystem.h"

SPHSystem::SPHSystem(SceneManager *mgr)
{
	// r = 100 unit
	sceneMgr = mgr;

	Entity *ent = sceneMgr->createEntity("ball", "sphere.mesh");
	SceneNode *snode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(ent);

	SPHParticle *particle = new SPHParticle(snode, 1, 1, Vector3::ZERO);
	particles.push_back(particle);
	snode->scale(0.01, 0.01, 0.01);

	cout << ent->getBoundingBox().getMaximum().x - ent->getBoundingBox().getMinimum().x << endl;
}

void SPHSystem::Update()
{
	for (int i=0;i<particles.size();++i) {
		particles[i]->Update(0.01);
	}
}