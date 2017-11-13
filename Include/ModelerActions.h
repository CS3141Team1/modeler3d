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
    }
private:
    Modeler3D* mModeler;
    Camera* mCamera;
    int32 mZoom;
};

class RotateAction : public Gui::IAction
{
public:
	RotateAction(Modeler3D* modeler, Camera* camera, int32 axis, int32 direction) : mModeler(modeler), mCamera(camera), mAxis(axis), mDirection(direction)
	{
		mAngle = mDirection * Math::ToRadians(20.0f);
		if (axis == 2)
		{
			mQ = Math::Quaternionf::AxisAngle(Math::Vector3f(0, 1, 0), mAngle);

		}
		else if (axis == 1)
		{
			mQ = Math::Quaternionf::AxisAngle(Math::Vector3f(1, 0, 0), mAngle);
		}
	}
    ~RotateAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	std::cout << "Rotated 20 degrees" << std::endl;

		if (mAxis == 2)
		{
			mCamera->UpdateYaw(mAngle);
			mCamera->SetRotation();
			mCamera->SetPosition(Math::Rotate(Core::Math::Vector3f(0, 0, mModeler->GetZoom()), mCamera->GetRotation()));
		}
		else if (mAxis == 1)
		{
			mCamera->UpdatePitch(mAngle);
			mCamera->SetRotation();
			mCamera->SetPosition(Math::Rotate(Core::Math::Vector3f(0, 0, mModeler->GetZoom()), mCamera->GetRotation()));
		}
    }
private:
    Modeler3D* mModeler;
    Camera* mCamera;
    int32 mAxis;
    int32 mDirection;
    Math::Quaternionf mQ;
    float32 mAngle;
};

class ScreenMoveAction : public Gui::IMoveAction
{
public:
    ScreenMoveAction(Modeler3D* m) : mModeler(m) {}
    ~ScreenMoveAction() {}

    void OnActionPerformed(Gui::Widget* caller, int32 x, int32 y, int32 dx, int32 dy, uint32 buttons)
    {
        if (buttons & 4)
        {
            mModeler->GetCamera()->UpdateYaw(-dx * Math::ToRadians(0.2));
            mModeler->GetCamera()->UpdatePitch(dy * Math::ToRadians(0.2));
            mModeler->GetCamera()->SetRotation();
            mModeler->GetCamera()->SetPosition(Math::Rotate(Core::Math::Vector3f(0, 0, mModeler->GetZoom()), mModeler->GetCamera()->GetRotation()));
        }
    }
private:
    Modeler3D* mModeler;
};

class ResetAction : public Gui::IAction
{
public:
	ResetAction(Modeler3D* modeler, Camera* camera) : mModeler(modeler), mCamera(camera) {}
    ~ResetAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	mCamera->SetRotation(0.0,0.0);
    	mCamera->SetPosition(Math::Vector3f(0,0,1));
    	mModeler->SetZoom(1);
    	std::cout << "Reset camera angle" << std::endl;
    }
private:
    Modeler3D* mModeler;
    Camera* mCamera;
};

}
