#pragma once

#include "IGraphicsDevice.h"

namespace Video
{

class OglGraphicsDevice : public IGraphicsDevice
{
public:
    OglGraphicsDevice();
    ~OglGraphicsDevice();

    void SetClearColor(float32 r, float32 g, float32 b, float32 a = 1.0);
    void Clear(bool color = true, bool depth = true);
};

}
