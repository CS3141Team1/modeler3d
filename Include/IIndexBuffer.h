#pragma once

#include "BufferHint.h"
#include "Types.h"

namespace Video
{

class IIndexBuffer
{
public:
    virtual ~IIndexBuffer() {}

    virtual void Release() = 0;
    virtual bool IsReleased() const = 0;

    virtual uint Length() const = 0;

    virtual BufferHint GetBufferHint() const = 0;
    virtual void SetBufferHint(BufferHint hint) = 0;

    virtual void GetData(void* out, uint start, uint count) const = 0;
    virtual void SetData(const void* data, uint start, uint count) = 0;
};

}
