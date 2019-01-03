#include "SPHSystem.h"

SPHSystem::SPHSystem(SceneManager *mgr)
{
	// r = 100 unit
	sceneMgr = mgr;
	time = 0;

}
void SPHSystem::createParticle(float m, float r, Vector3 v){
	Entity *ent = sceneMgr->createEntity("sphere.mesh");
	SceneNode *snode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(ent);
	snode->setPosition(Vector3(0,300,0));

	SPHParticle *particle = new SPHParticle(snode, 1, 1, Vector3::ZERO);
	particles.push_back(particle);
	float scaleSize = r/100;
	snode->scale(scaleSize, scaleSize, scaleSize);
}
void SPHSystem::Update(const Ogre::FrameEvent& evt)
{
	for (int i=0;i<particles.size();++i) {
		particles[i]->Update(0.01);
	}
	time += evt.timeSinceLastFrame;
	if(time > 0.3){
		float particleRadius = DATA_READER::getParticleRadius();
		cout << "----------------------------------123particle radius = " << particleRadius <<endl;
		createParticle(1, particleRadius, Vector3::ZERO);
		time = 0;
	}
}