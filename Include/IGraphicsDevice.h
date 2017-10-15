#pragma once

#include "Types.h"

namespace Video
{

class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    virtual void SetClearColor(float32 r, float32 g, float32 b, float32 a = 1.0) = 0;
    virtual void Clear(bool color = true, bool depth = true) = 0;
};

}
