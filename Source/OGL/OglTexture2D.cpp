#include "OGL/OglTexture2D.h"

#include <iostream>
using namespace std;

namespace Video
{

OglTexture2D::OglTexture2D(uint width, uint height)
    : mId(0),
      mWidth(width),
      mHeight(height)
{
    glGenTextures(1, &mId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

OglTexture2D::~OglTexture2D()
{
    Release();
}

void OglTexture2D::Release()
{
    if (mId)
    {
        glDeleteTextures(1, &mId);
        mId = 0;
    }
}

uint OglTexture2D::GetWidth() const
{
    return mWidth;
}

uint OglTexture2D::GetHeight() const
{
    return mHeight;
}

void OglTexture2D::GetData(uint8* out, uint x, uint y, uint w, uint h) const
{
    // TODO
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*) in);
    cout << "TEXTURE2D GET DATA NOT IMPLEMENTED" << endl;
}

void OglTexture2D::SetData(const uint8* in, uint x, uint y, uint w, uint h)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, (const void*) in);
}

}
