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
	ZoomAction(Camera* camera, int32 zoom) : mCamera(camera), mZoom(zoom) {}
    ~ZoomAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
    	std::cout << "Zoom set to: " << mZoom << std::endl;
        mCamera->SetPosition(Math::Vector3f(0,2,mZoom));
    }
private:
    Camera* mCamera;
    int32 mZoom;
};

}
