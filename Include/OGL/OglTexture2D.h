#pragma once

#include <GL/glew.h>

#include "ITexture2D.h"

namespace Video
{

class OglTexture2D : public ITexture2D
{
public:
    OglTexture2D(uint width, uint height);
    ~OglTexture2D();

    void Release();

    uint GetWidth() const;
    uint GetHeight() const;

    void GetData(uint8* out, uint x, uint y, uint w, uint h) const;
    void SetData(const uint8* in, uint x, uint y, uint w, uint h);

    GLuint GetId() const { return mId; }
private:
    GLuint mId;
    uint mWidth, mHeight;
};

}
