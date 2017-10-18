#pragma once

#include "IGraphicsDevice.h"

namespace Video
{

class OglGraphicsDevice : public IGraphicsDevice
{
public:
    OglGraphicsDevice();
    ~OglGraphicsDevice();

    IVertexBuffer* CreateVertexBuffer(VertexFormat format, uint count, BufferHint hint = BufferHint::Dynamic);
    IGeometry* CreateGeometry();

    void SetClearColor(float32 r, float32 g, float32 b, float32 a = 1.0);
    void Clear(bool color = true, bool depth = true);

    virtual const IGeometry* GetGeometry() const { return mGeometry; }
    virtual IGeometry* GetGeometry() { return mGeometry; }

    virtual void SetGeometry(IGeometry* geom);

    virtual void Draw(Primitive prim, uint start, uint primCount);
private:
    IGeometry* mGeometry = nullptr;
};

}
