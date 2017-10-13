#include "Ogl/OglGraphicsDevice.h"

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

OglGraphicsDevice::OglGraphicsDevice(SDL_GLContext context)
    : mContext(context)
{

}

OglGraphicsDevice::~OglGraphicsDevice()
{
}

ITexture2D* OglGraphicsDevice::CreateTexture(uint width, uint height)
{
    // TODO
    return NULL;
}

IGeometry* OglGraphicsDevice::CreateGeometry()
{
    // TODO
    return NULL;
}

IIndexBuffer* OglGraphicsDevice::CreateIndexBuffer(uint length, BufferHint hint)
{
    // TODO
    return NULL;
}

IVertexBuffer* OglGraphicsDevice::CreateVertexBuffer(VertexFormat format,
        uint length, BufferHint hint)
{
    // TODO
    return NULL;
}

IShader* OglGraphicsDevice::CreateShader(const std::string& vSource,
        const std::string& fSource)
{
    // TODO
    return NULL;
}

ITexture* OglGraphicsDevice::GetTexture(uint index) const
{
    // TODO
    return NULL;
}

IGeometry* OglGraphicsDevice::GetGeometry() const
{
    // TODO
    return NULL;
}

IShader* OglGraphicsDevice::GetShader() const
{
    // TODO
    return NULL;
}

void OglGraphicsDevice::SetTexture(uint index, ITexture* tex)
{

}

void OglGraphicsDevice::SetGeometry(IGeometry* geom)
{
}

void OglGraphicsDevice::SetShader(IShader* shader)
{
}

}
