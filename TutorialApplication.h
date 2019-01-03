//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Chien-Yao Huang
\n
My ID: 0656651
\n
My Email: hk850522@gmail.com
\n Date: 2018/09/20

This is an assignment of 3D Game Programming
*/

////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "SPHSystem.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
    virtual void chooseSceneManager(void);

    virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	
    virtual bool frameStarted(const Ogre::FrameEvent& evt);

protected:

	void createViewport_00(void);
	void createViewport_01(void);
	void createCamera_00();
	/*!
	\brief Create a camera

	Create a camera for the second screen.

	\return None.
	*/
	void createCamera_01();

	/*!
	\brief Create the main scene.

	In this scene, it contains two penguins and several cubes which is arranged in particular shape

	\return None.
	*/
	void createScene_00();
	/*!
	\brief Create the second scene.

	In this scene, it contains a sphere

	\return None.
	*/
	void createScene_01();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    //
    // Add your own stuff.
    //
	
	
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];

	SPHSystem *sph;
    //
    // Add your own stuff.
    //   
};


#endif // #ifndef __BasicTutorial_00_h_