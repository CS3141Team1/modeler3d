#pragma once

#include <vector>

#include "IIndexBuffer.h"
#include "IVertexBuffer.h"
#include "Types.h"

namespace Video
{

class IGeometry
{
public:
    virtual ~IGeometry() {}

    virtual void Release() = 0;
    virtual bool IsReleased() const = 0;

    virtual uint GetVertexBufferCount() const = 0;
    virtual bool HasIndexBuffer() const = 0;

    virtual IVertexBuffer* GetVertexBuffer(uint index) const = 0;
    virtual IIndexBuffer* GetIndexBuffer() const = 0;

    virtual void SetVertexBuffers(const std::vector<IVertexBuffer*>& buffers, uint offset = 0) = 0;
    virtual void SetVertexBuffers(const IVertexBuffer** buffers, uint count, uint offset = 0) = 0;
    virtual void SetVertexBuffer(IVertexBuffer* buffer) = 0;
    virtual void SetIndexBuffer(IIndexBuffer* buffer) = 0;
};

}
