#pragma once

#include "BufferHint.h"

namespace Video
{

class IIndexBuffer
{
public:
    virtual ~IIndexBuffer() {}

    BufferHint GetBufferHint() const = 0;
    void SetBufferHint(BufferHint hint) = 0;
};

}
