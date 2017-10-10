#pragma once

#include "IGraphicsDevice.h"
#include "Types.h"

namespace Core
{

class IEngine;

class Application
{
public:
    Application(IEngine* engine);
    virtual ~Application() {}

    virtual void OnInit() {}
    virtual void OnUpdate(float64 dt) {}
    virtual void OnRender() {}
    virtual void OnExit() {}
protected:
    IEngine const* Engine;
    Video::IGraphicsDevice const* GraphicsDevice;
};

}

#include "IEngine.h"
