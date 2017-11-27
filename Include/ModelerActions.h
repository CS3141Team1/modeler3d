#pragma once

#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

#include "Modeler3D.h"
#include "Types.h"

#include "GUI/IAction.h"
#include "GUI/Widget.h"
#include "Math/VectorMath.h"

namespace Core
{

/**
 * Action called when one of the buttons for loading a file is clicked.
 */
class LoadAction : public Gui::IAction
{
public:
    LoadAction(Modeler3D* modeler, std::string file) : mModeler(modeler), mFile(file) {}
    ~LoadAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
        std::cout << "Loading file: " << mFile << std::endl;
        if(mFile == "Assets/dragon-big.obj")
        	std::cout << "Note, dragon-big.obj is very large and can take up to 30sec to load" << std::endl;
        mModeler->LoadObj(mFile);
    }
private:
    Modeler3D* mModeler;
    std::string mFile;
};

/**
 * Action called when the zoom button is clicked.
 */
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

/**
 * Action called when rotation buttons are clicked.
 */
class RotateAction : public Gui::IAction
{
public:
	RotateAction(Modeler3D* modeler, Camera* camera, int32 axis, int32 direction) : mModeler(modeler), mCamera(camera), mAxis(axis), mDirection(direction)
	{
		mAngle = mDirection * Math::ToRadians(20.0f);
		//Sets quaternion based on axis
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

    	//performs rotation based on which button is being clicked
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

/**
 * Action called when moving the mouse and clicking the mouse.
 */
class ScreenMoveAction : public Gui::IMoveAction
{
public:
    ScreenMoveAction(Modeler3D* m) : mModeler(m) {}
    ~ScreenMoveAction() {}

    void OnActionPerformed(Gui::Widget* caller, int32 x, int32 y, int32 dx, int32 dy, uint32 buttons)
    {
        if (buttons & 4) //checks if third mouse button (right click) is down for click and drag
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

/**
 * Action called when the camera reset button is clicked.
 */
class ResetAction : public Gui::IAction
{
public:
	ResetAction(Modeler3D* modeler, Camera* camera) : mModeler(modeler), mCamera(camera) {}
    ~ResetAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	//set all angles to 0, and default position/zoom
    	mCamera->SetYaw(0.0);
    	mCamera->SetPitch(0.0);
    	mCamera->SetRotation(0.0,0.0);
    	mCamera->SetPosition(Math::Vector3f(0,0,1));
    	mModeler->SetZoom(1);
    	std::cout << "Reset camera angle" << std::endl;
    }
private:
    Modeler3D* mModeler;
    Camera* mCamera;
};

/**
 * Action called when the button for changing between orthographic
 * and perspective view is clicked.
 */
class ChangeViewAction : public Gui::IAction
{
public:
	ChangeViewAction(Modeler3D* modeler, Camera* camera) : mModeler(modeler), mCamera(camera) {}
    ~ChangeViewAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	Camera::Projection proj = mCamera->ToggleProjectionType();
    	if(proj == Camera::Projection::ORTHOGRAPHIC) //if changed to orthographic
    	{
    		std::cout << "Switched to orthographic" << std::endl;
    		((Gui::Button*)widget)->SetText("To Perspective");
    		mModeler->SetZoom((int32)(mModeler->GetZoom() * 0.1));
    	}
    	else //if changed to perspective
    	{
    		std::cout << "Switched to perspective" << std::endl;
    		((Gui::Button*)widget)->SetText("To Orthographic");
    		mModeler->SetZoom((int32)(mModeler->GetZoom() * 10));
    	}
    }
private:
    Modeler3D* mModeler;
    Camera* mCamera;
};

/**
 * Action called when a button for changing colors is clicked.
 */
class ChangeColorAction : public Gui::IAction
{
public:
	//0 is R, 1 is G, 2 is B
	ChangeColorAction(Modeler3D* modeler, int32 rgb, float32 amount) : mModeler(modeler), mRgb(rgb), mAmount(amount) {}
    ~ChangeColorAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	Math::Vector3f color = mModeler->GetColor();
    	if(mRgb == 0) //red
    	{
    		color[0] += mAmount;
    		color[0] = (color[0] > 1 ? 1 : (color[0] < 0 ? 0 : color[0]));
    	}
    	else if(mRgb == 1) //green
    	{
    		color[1] += mAmount;
    		color[1] = (color[1] > 1 ? 1 : (color[1] < 0 ? 0 : color[1]));
    	}
    	else //blue
    	{
    		color[2] += mAmount;
    		color[2] = (color[2] > 1 ? 1 : (color[2] < 0 ? 0 : color[2]));
    	}
    	mModeler->SetColor(color);
    }
private:
    Modeler3D* mModeler;
    int32 mRgb;
    float32 mAmount;
};

/**
 * Action called to scale the model.
 */
class ScaleAction : public Gui::IAction
{
public:
	ScaleAction(Modeler3D* modeler, float32 amount, Gui::Widget* display) : mModeler(modeler), mAmount(amount), mDisplay(display) {}
    ~ScaleAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	Math::Vector3f scale = mModeler->GetScale();
    	scale += mAmount;
    	scale = (scale[0] < 0.1 ? Math::Vector3f(0.1) : scale);
    	std::stringstream stream;
    	stream << std::fixed << std::setprecision(1) << scale[0];
    	std::string s = stream.str();
    	std::string text = "Cur. Scale: " + s + "x";
    	((Gui::Button*)mDisplay)->SetText(text);
    	mModeler->SetScale(scale);
    }
private:
    Modeler3D* mModeler;
    float32 mAmount;
    Gui::Widget* mDisplay;
};

/**
 * Action called that does nothing.
 */
class NoOpAction : public Gui::IAction
{
public:
	NoOpAction() {}
    ~NoOpAction() {}

    void OnActionPerformed(Gui::Widget* widget) {}
};

}
