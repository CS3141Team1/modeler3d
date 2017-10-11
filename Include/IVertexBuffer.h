#pragma once

#include "BufferHint.h"

namespace Video
{

class IVertexBuffer
{
public:
    virtual ~IVertexBuffer() {}

    BufferHint GetBufferHint() const = 0;
    void SetBufferHint(BufferHint hint) = 0;
};

}
