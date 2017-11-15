#pragma once

#include "Application.h"
#include "Camera.h"
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

    virtual void SetZoom(float32 zoom);

    void LoadObj(const std::string& file);

    float32 GetZoom() const { return mZoom; }

    Camera* GetCamera() { return mCamera; }

private:
    Gui::Environment* mEnv;
    Video::GuiRenderer* mGuiRenderer;
    Video::IShader* mShader;
    Video::IGeometry* mGeometry;
    Video::IVertexBuffer* mVbo;
    float32 mAngle;
    SdlMouse* mMouse;
    Camera* mCamera;
    float32 mZoom;
};

}
