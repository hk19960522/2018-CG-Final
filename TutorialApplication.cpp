////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2018/09/20
////////////////////////////////////////
// Student Name: ¶À«Ø³ó
// Student ID: 0656651
// Student Email: hk850522@gmail.com
//
////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace Ogre;

const float PI = 3.141592654;

BasicTutorial_00::BasicTutorial_00(void) 
{

}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
    //
    // add your own stuff
    //

}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	// add your own stuff
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("LittleCam");
	mCamera->setPosition(Ogre::Vector3(0,350,0));
	mCamera->lookAt(Ogre::Vector3(0.0001,0,0));
	mCamera->setNearClipDistance(5);
	mCamera = mCameraArr[0];
}


void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.7, 0.7));

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
    // add your own stuff
	mCamera = mCameraArr[1];
	Viewport* vp = mWindow->addViewport(mCamera, 1, 0.75, 0, 0.25, 0.25);
	//float Width = 0.25, Height = 0.25;

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0.7));
	vp->setOverlaysEnabled(false);
	mViewportArr[1] = vp;
	//mCamera = mCameraArr[0];
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];

	// ambient light and shadow
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.7, 0.7, 0.7));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// add light
	Light *light01 = mSceneMgr->createLight("Light1"); 
	light01->setType(Light::LT_POINT); 
	light01->setPosition(Vector3(150, 250, 100));
	light01->setDiffuseColour(1.0, 1.0, 0.0); 
	light01->setSpecularColour(1.0, 0.0, 1.0); 
	
	Light *light02 = mSceneMgr->createLight("Light2"); 
	light02->setType(Light::LT_POINT); 
	light02->setPosition(Vector3(-150, 300, 250));
	light02->setDiffuseColour(0.0, 1.0, 1.0); 
	light02->setSpecularColour(1.0, 0.0, 1.0); 
	
	
}

void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff
	mSceneMgr = mSceneMgrArr[1];
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Light *light = mSceneMgr->createLight();
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 150, 250)); 
	light->setDiffuseColour(0.0, 0.0, 1.0);	
	light->setSpecularColour(0.0,0.0, 1.0);
	
	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane(
	"ground01", 										
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			plane, 
			1000,1000, 	// width, height
			20,20, 		// x- and y-segments
			true, 		// normal
			1, 			// num texture sets
			5,5, 		// x- and y-tiles
			Vector3::UNIT_Z	// upward vector
		);
	Entity *ent = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

	ent = mSceneMgr->createEntity("Sphere", "sphere.mesh");
	ent->setMaterialName("Examples/green");
	SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->setPosition(50, 50, 0);
	snode->scale(0.5, 0.2, 0.3);
	snode->attachObject(ent);
}

void BasicTutorial_00::createViewports(void)
{
    //Do not modify
	createViewport_00();
}

void BasicTutorial_00::createCamera(void) {
    //Do not modify
	createCamera_00();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) 
{
	createScene_00();
	mSceneMgr = mSceneMgrArr[0]; 
    mCamera = mCameraArr[0];
}

bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    
    // Do not delete this line
	bool flg = true;
    BaseApplication::keyPressed(arg);

    return flg;
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
   

    BaseApplication::keyReleased(arg);
    return flg;
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);

	// Update Penguin
	
	
    return flg;
}
int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}

////////////////////////////////////////
// DO NOT DELETE THIS LINE: 2018/09/20. 3D Game Programming
////////////////////////////////////////