#pragma once

#include "IGraphicsResource.h"
#include "IVertexBuffer.h"
#include "Types.h"

namespace Video
{

class IGeometry : public IGraphicsResource
{
public:
    virtual ~IGeometry() {}

    virtual uint GetVertexBufferCount() const = 0;
    virtual const IVertexBuffer* GetVertexBuffer(uint index) const = 0;
    virtual IVertexBuffer* GetVertexBuffer(uint index) = 0;

    virtual void SetVertexBuffer(IVertexBuffer* vbo) = 0;
    virtual void SetVertexBuffers(IVertexBuffer** vbos, uint count) = 0;
};

}
