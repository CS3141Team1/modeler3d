#pragma once

#include "Types.h"

namespace Video
{

class IIndexBuffer;
class ITexture2D;
class IVertexArray;
class IVertexBuffer;

class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    virtual ITexture2D* CreateTexture(uint width, uint height) = 0;
};

}
