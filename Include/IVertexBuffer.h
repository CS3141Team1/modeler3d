#pragma once

#include "IGraphicsResource.h"
#include "Types.h"
#include "VertexFormat.h"

namespace Video
{

class IVertexBuffer : public IGraphicsResource
{
public:
    virtual ~IVertexBuffer() {}

    virtual const VertexFormat& GetFormat() const = 0;

    virtual uint GetLength() const = 0;
    virtual uint GetSizeInBytes() const { return GetLength() * GetFormat().GetSizeInBytes(); }

    virtual void GetData(void* out, uint start, uint count) const = 0;
    virtual void SetData(void* in, uint start, uint count) = 0;
};

}
