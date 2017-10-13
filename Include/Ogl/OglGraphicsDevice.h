#pragma once

#include <SDL2/SDL.h>

#include "IGraphicsDevice.h"

namespace Video
{

class OglGraphicsDevice : public IGraphicsDevice
{
public:
    OglGraphicsDevice(SDL_GLContext context);
    ~OglGraphicsDevice();

    virtual ITexture2D* CreateTexture(uint width, uint height);

    virtual IGeometry* CreateGeometry();
    virtual IIndexBuffer* CreateIndexBuffer(uint length, BufferHint hint = BufferHint::Dynamic);
    virtual IVertexBuffer* CreateVertexBuffer(VertexFormat format, uint length, BufferHint hint = BufferHint::Dynamic);

    virtual IShader* CreateShader(const std::string& vSource, const std::string& fSource);

    virtual ITexture* GetTexture(uint index) const;
    virtual IGeometry* GetGeometry() const;
    virtual IShader* GetShader() const;

    virtual void SetTexture(uint index, ITexture* tex);
    virtual void SetGeometry(IGeometry* geom);
    virtual void SetShader(IShader* shader);
private:
    SDL_GLContext mContext;

};

}
