#pragma once

#include "IGraphicsDevice.h"

#include "OGL/OglGeometry.h"
#include "OGL/OglShader.h"

namespace Video
{

class OglGraphicsDevice : public IGraphicsDevice
{
public:
    OglGraphicsDevice();
    ~OglGraphicsDevice();

    void Init();

    IVertexBuffer* CreateVertexBuffer(VertexFormat format, uint count, BufferHint hint = BufferHint::Dynamic);
    IShader* CreateShader(const std::string& vertex, const std::string& fragment);
    IGeometry* CreateGeometry();

    void SetClearColor(float32 r, float32 g, float32 b, float32 a = 1.0);
    void Clear(bool color = true, bool depth = true);

    const IGeometry* GetGeometry() const { return mGeometry; }
    IGeometry* GetGeometry() { return mGeometry; }
    const IShader* GetShader() const { return mShader; }
    IShader* GetShader() { return mShader; }

    void SetGeometry(IGeometry* geom);
    void SetShader(IShader* shader);

    void Draw(Primitive prim, uint start, uint primCount);

    float32 Ratio = 1.3333;
private:
    OglGeometry* mGeometry = nullptr;
    OglShader* mShader = nullptr;
};

}
