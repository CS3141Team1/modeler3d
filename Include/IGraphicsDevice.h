#pragma once

#include "BufferHint.h"
#include "ITexture.h"
#include "Types.h"

namespace Video
{

class IIndexBuffer;
class IVertexArray;
class IVertexBuffer;

class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    virtual ITexture2D* CreateTexture(uint width, uint height) = 0;

    virtual IIndexBuffer* CreateIndexBuffer(BufferHint hint) = 0;
};

}
