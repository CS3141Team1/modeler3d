#pragma once

#include "Types.h"

namespace Video
{

class ITexture2D
{
public:
    virtual ~ITexture2D() {}

    virtual uint GetWidth() const = 0;
    virtual uint GetHeight() const = 0;

    void GetData(uint32* out, uint start, uint count) const = 0;
    void SetData(const uint32* in, uint start, uint count) = 0;
};

}
