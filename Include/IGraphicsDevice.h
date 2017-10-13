#pragma once

#include <string>

#include "BufferHint.h"
#include "IGeometry.h"
#include "IIndexBuffer.h"
#include "IShader.h"
#include "ITexture.h"
#include "IVertexBuffer.h"
#include "Types.h"
#include "VertexFormat.h"

namespace Video
{

class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    virtual ITexture2D* CreateTexture(uint width, uint height) = 0;

    virtual IGeometry* CreateGeometry() = 0;
    virtual IIndexBuffer* CreateIndexBuffer(uint length, BufferHint hint = BufferHint::Dynamic) = 0;
    virtual IVertexBuffer* CreateVertexBuffer(VertexFormat format, uint length, BufferHint hint = BufferHint::Dynamic) = 0;

    virtual IShader* CreateShader(const std::string& vSource, const std::string& fSource) = 0;

    virtual ITexture* GetTexture(uint index) const = 0;
    virtual IGeometry* GetGeometry() const = 0;
    virtual IShader* GetShader() const = 0;

    virtual void SetTexture(uint index, ITexture* tex) = 0;
    virtual void SetGeometry(IGeometry* geom) = 0;
    virtual void SetShader(IShader* shader) = 0;
};

}
