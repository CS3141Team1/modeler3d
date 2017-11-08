#pragma once

#include "IGraphicsResource.h"
#include "Types.h"

namespace Video
{

class ITexture2D : public IGraphicsResource
{
public:
    virtual ~ITexture2D() {}

    virtual uint GetWidth() const = 0;
    virtual uint GetHeight() const = 0;

    virtual void GetData(uint8* out, uint x, uint y, uint w, uint h) const = 0;
    virtual void SetData(const uint8* in, uint x, uint y, uint w, uint h) = 0;
};

}
