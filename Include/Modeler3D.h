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

    /**
     * Called when initializing application
     */
    virtual void OnInit();

    /**
     * Called when application needs to update
     */
    virtual void OnUpdate(float64 dt);

    /**
     * Called when application needs to render
     */
    virtual void OnRender();

    /**
     * Called when application is closing
     */
    virtual void OnDestroy();

    /**
     * Sets camera zoom level
     */
    void SetZoom(float32 zoom);

    /**
     * Loads a .obj model into the program
     */
    void LoadObj(const std::string& file);

    /**
     * @return zoom level
     */
    float32 GetZoom() const { return mZoom; }

    /**
     * @return model color
     */
    Math::Vector3f GetColor() const { return mColor; }

    /**
     * Set model color
     */
    void SetColor(Math::Vector3f color);

    /**
     * @return model scale
     */
    Math::Vector3f GetScale() const { return mScale; }

    /**
     * Set the model's scale
     */
    void SetScale(Math::Vector3f scale);

    /**
     * @return pointer to modeler camera
     */
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
    Math::Vector3f mColor;
    Math::Vector3f mScale;
};

}
