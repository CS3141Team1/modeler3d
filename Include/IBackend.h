#pragma once

#include "IGraphicsDevice.h"
#include "IWindow.h"

namespace Core
{

class IBackend
{
public:
    virtual ~IBackend() {}

    virtual void Init() = 0;
    virtual void Destroy() = 0;

    virtual IWindow* GetWindow() = 0;
    virtual Video::IGraphicsDevice* GetGraphicsDevice() = 0;
};

}
