#pragma once

#include "IGeometry.h"
#include "IVertexBuffer.h"
#include "Types.h"

namespace Video
{

enum class Primitive
{
    TriangleList
};

enum class BufferHint
{
    Static,
    Dynamic,
    Stream
};

class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    virtual IVertexBuffer* CreateVertexBuffer(VertexFormat format, uint count, BufferHint hint = BufferHint::Dynamic) = 0;
    virtual IGeometry* CreateGeometry() = 0;

    virtual void SetClearColor(float32 r, float32 g, float32 b, float32 a = 1.0) = 0;
    virtual void Clear(bool color = true, bool depth = true) = 0;

    virtual const IGeometry* GetGeometry() const = 0;
    virtual IGeometry* GetGeometry() = 0;

    virtual void SetGeometry(IGeometry* geom) = 0;

    virtual void Draw(Primitive prim, uint start, uint primCount) = 0;
};

}
