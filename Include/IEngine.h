#pragma once

#include "Application.h"
#include "IGraphicsDevice.h"
#include "Types.h"

namespace Core
{

class IWindow;

class IEngine
{
public:
    virtual ~IEngine() {}

    virtual Float64 GetFrames() = 0;
    virtual Float64 GetUpdates() = 0;

    virtual IWindow* GetWindow() = 0;
    virtual Video::IGraphicsDevice* GetGraphicsDevice() = 0;

    virtual void Start(Application* app) = 0;
    virtual void Stop() = 0;
};

}
