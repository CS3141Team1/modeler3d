#pragma once

#include "Application.h"
#include "Types.h"

#include "GUI/Environment.h"
#include "SDL2/SdlMouse.h"

namespace Video
{

class GuiRenderer;

}

namespace Core
{

/**
 * 3D modeler class
 */
class Modeler3D : public Application
{
public:
    Modeler3D(IBackend* backend);
    ~Modeler3D();

    virtual void OnInit();
    virtual void OnUpdate(float64 dt);
    virtual void OnRender();
    virtual void OnDestroy();

    void LoadObj(const std::string& file);

private:
    Gui::Environment* mEnv;
    Video::GuiRenderer* mGuiRenderer;
    Video::IShader* mShader;
    Video::IGeometry* mGeometry;
    Video::IVertexBuffer* mVbo;
    float32 mAngle;
};

}
