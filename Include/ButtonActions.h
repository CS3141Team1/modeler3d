#pragma once

#include <cstdlib>
#include <string>

#include "Modeler3D.h"
#include "Types.h"

#include "GUI/IAction.h"
#include "GUI/Widget.h"
#include "Math/VectorMath.h"

namespace Core
{

class LoadAction : public Gui::IAction
{
public:
    LoadAction(Modeler3D* modeler, std::string file) : mModeler(modeler), mFile(file) {}
    ~LoadAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
        std::cout << "Loading file: " << mFile << std::endl;
        if(mFile == "Assets/dragon.obj")
        	std::cout << "Note, dragon.obj is very large and can take up to 30sec to load" << std::endl;
        mModeler->LoadObj(mFile);
    }
private:
    Modeler3D* mModeler;
    std::string mFile;
};

class ZoomAction : public Gui::IAction
{
public:
	ZoomAction(Modeler3D* modeler, Camera* camera, int32 zoom) : mModeler(modeler), mCamera(camera), mZoom(zoom) {}
    ~ZoomAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	std::cout << "Zoom set to: " << mZoom << std::endl;
    	mModeler->SetZoom(mZoom);
        mCamera->SetPosition(Math::Vector3f(0,0,mZoom));
    }
private:
    Modeler3D* mModeler;
    Camera* mCamera;
    int32 mZoom;
};

class RotateAction : public Gui::IAction
{
public:
	RotateAction(Modeler3D* modeler, Camera* camera, int32 axis, int32 direction) : mModeler(modeler), mCamera(camera), mAxis(axis), mDirection(direction) {}
    ~RotateAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	std::cout << "Rotated ~10 degrees" << std::endl;
    	float32 angle = mDirection * 3.1415926535897/20.0;
		Math::Quaternionf q;
		if (mAxis == 2)
		{
			mCamera->UpdateYaw(angle);
			q = Math::Quaternionf::AxisAngle(Math::Vector3f(0, 1, 0), angle);

		} else if (mAxis == 1)
		{
			mCamera->UpdatePitch(angle);
			q = Math::Quaternionf::AxisAngle(Math::Vector3f(1, 0, 0), angle);
		}

    	mCamera->SetRotation();
        mCamera->Rotate(q);
    }
private:
    Modeler3D* mModeler;
    Camera* mCamera;
    int32 mAxis;
    int32 mDirection;
};

}
