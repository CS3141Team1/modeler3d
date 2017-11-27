#include "OGL/OglGraphicsDevice.h"

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/Sdl2Window.h>

#include "lodepng.h"

#include "Math/ModelerMath.h"
#include "Math/Matrix4.h"

#include "OGL/OglGeometry.h"
#include "OGL/OglIndexBuffer.h"
#include "OGL/OglTexture2D.h"
#include "OGL/OglVertexBuffer.h"

using namespace std;
using namespace Core;
using namespace Core::Math;

/*
 * TODO
 *
 * This is incredibly inefficient because I just needed to
 * get it to work, I will make this better later.
 */

namespace Video
{

static std::string AttributeName(Attribute attrib)
{
    switch (attrib)
    {
    case Attribute::Position: return "aPosition";
    case Attribute::Normal: return "aNormal";
    case Attribute::Color: return "aColor";
    case Attribute::TexCoord0: return "aTexCoord0";
    case Attribute::TexCoord1: return "aTexCoord1";
    case Attribute::TexCoord2: return "aTexCoord2";
    case Attribute::TexCoord3: return "aTexCoord3";
    default: return "[null]";
    }
}

OglGraphicsDevice::OglGraphicsDevice(Sdl2Window* window)
    : mWindow(window),
      mTextures(16)
{
}

OglGraphicsDevice::~OglGraphicsDevice()
{
}

void OglGraphicsDevice::Init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OglGraphicsDevice::SetClearColor(float32 r, float32 g, float32 b, float32 a)
{
    glClearColor(r, g, b, a);
}

IVertexBuffer* OglGraphicsDevice::CreateVertexBuffer(VertexFormat format, uint count, BufferHint hint)
{
    OglVertexBuffer* vbo = new OglVertexBuffer(format, count); //, hint);
    return vbo;
}

IIndexBuffer* OglGraphicsDevice::CreateIndexBuffer(uint count, BufferHint hint)
{
    OglIndexBuffer* ibo = new OglIndexBuffer(count); //, hint);
    return ibo;
}

IGeometry* OglGraphicsDevice::CreateGeometry()
{
    return new OglGeometry;
}

void OglGraphicsDevice::Clear(bool color, bool depth)
{
    GLuint flags = 0;

    if (color) flags |= GL_COLOR_BUFFER_BIT;
    if (depth) flags |= GL_DEPTH_BUFFER_BIT;

    if (flags) glClear(flags);
}

void OglGraphicsDevice::SetGeometry(IGeometry* geom)
{
    mGeometry = dynamic_cast<OglGeometry*>(geom);
}

IShader* OglGraphicsDevice::CreateShader(const std::string& vertex,
        const std::string& fragment)
{
    return new OglShader(vertex, fragment);
}

void OglGraphicsDevice::SetShader(IShader* shader)
{
    mShader = dynamic_cast<OglShader*>(shader);
}

float Angle = 0.0;

void OglGraphicsDevice::Draw(Primitive prim, uint start, uint primCount)
{
    if (mGeometry == nullptr) return;
    if (mShader == nullptr) return;

    // bind current shader
    glUseProgram(mShader->GetId());

    Angle += Math::ToRadians(0.3);

    for (uint i = 0; i < 16; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        OglTexture2D* tex = mTextures[i];
        glBindTexture(GL_TEXTURE_2D, tex == nullptr ? 0 : tex->GetId());
    }

    unordered_set<int> usedAttribs;

    for (uint i = 0; i < mGeometry->GetVertexBufferCount(); i++)
    {
        OglVertexBuffer* vbo = dynamic_cast<OglVertexBuffer*>(mGeometry->GetVertexBuffer(i));

        if (vbo)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo->GetId());

            const VertexFormat& format = vbo->GetFormat();

            for (uint j = 0; j < format.GetElementCount(); j++)
            {
                const VertexElement& elem = format.GetElement(j);

                int attribId = static_cast<int>(elem.Attrib);

                if (usedAttribs.find(attribId) == usedAttribs.end())
                {
                    usedAttribs.insert(attribId);
                    string name = AttributeName(elem.Attrib);
//                    cout << "Found " << name << ": " << elem.Count << ", " << format.GetOffsetOf(j) << ", " << format.GetSizeInBytes() << ", " << glGetAttribLocation(mShader->GetId(), name.c_str()) << endl;

                    glVertexAttribPointer(
                            glGetAttribLocation(mShader->GetId(), name.c_str()),
                            elem.Count,
                            GL_FLOAT,
                            GL_FALSE,
                            format.GetSizeInBytes(),
                            reinterpret_cast<void*>(format.GetOffsetOf(j))
                    );
                    GLint location = glGetAttribLocation(mShader->GetId(), name.c_str());
//                    cout << location << " ";
                    glEnableVertexAttribArray(location);
                }
            }
        }
    }
//    cout << endl;

    glDrawArrays(GL_TRIANGLES, start, primCount * 3);
}

float32 OglGraphicsDevice::GetWidth() const
{
    return mWindow->GetWidth();
}

float32 OglGraphicsDevice::GetHeight() const
{
    return mWindow->GetHeight();
}

float32 OglGraphicsDevice::GetAspectRatio() const
{
    return mWindow->GetAspectRatio();
}

ITexture2D* OglGraphicsDevice::CreateTexture2D(const std::string& filename)
{
    vector<uint8> pixels;
    uint width, height;

    uint error = lodepng::decode(pixels, width, height, filename, LCT_RGBA);

    if (error)
    {
        cout << "Error reading image: " << filename << endl;
        return nullptr;
    }
    else
    {
        OglTexture2D* tex = new OglTexture2D(width, height);

        for (uint y = 0; y < height / 2; y++)
        {
            for (uint x = 0; x < width; x++)
            {
                for (uint i = 0; i < 4; i++)
                {
                    uint index1 = (x + y * width) * 4 + i;
                    uint index2 = (x + (height - y - 1) * width) * 4 + i;

                    pixels[index1] ^= pixels[index2];
                    pixels[index2] ^= pixels[index1];
                    pixels[index1] ^= pixels[index2];
                }
            }
        }
        tex->SetData(&pixels[0], 0, 0, width, height);
        return tex;
    }
}

void OglGraphicsDevice::DrawIndices(Primitive prim, uint start, uint primCount)
{
    if (mGeometry == nullptr) return;
    if (mShader == nullptr) return;

    // bind current shader
    glUseProgram(mShader->GetId());

    for (uint i = 0; i < 16; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        OglTexture2D* tex = mTextures[i];
        glBindTexture(GL_TEXTURE_2D, tex == nullptr ? 0 : tex->GetId());
    }

    unordered_set<int> usedAttribs;

    for (uint i = 0; i < mGeometry->GetVertexBufferCount(); i++)
    {
        OglVertexBuffer* vbo = dynamic_cast<OglVertexBuffer*>(mGeometry->GetVertexBuffer(i));

        if (vbo)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo->GetId());

            const VertexFormat& format = vbo->GetFormat();

            for (uint j = 0; j < format.GetElementCount(); j++)
            {
                const VertexElement& elem = format.GetElement(j);

                int attribId = static_cast<int>(elem.Attrib);

                if (usedAttribs.find(attribId) == usedAttribs.end())
                {
                    usedAttribs.insert(attribId);
                    string name = AttributeName(elem.Attrib);
//                    cout << "Found " << name << ": " << elem.Count << ", " << format.GetOffsetOf(j) << ", " << format.GetSizeInBytes() << ", " << glGetAttribLocation(mShader->GetId(), name.c_str()) << endl;

                    glVertexAttribPointer(
                            glGetAttribLocation(mShader->GetId(), name.c_str()),
                            elem.Count,
                            GL_FLOAT,
                            GL_FALSE,
                            format.GetSizeInBytes(),
                            reinterpret_cast<void*>(format.GetOffsetOf(j))
                    );
                    GLint location = glGetAttribLocation(mShader->GetId(), name.c_str());
                    glEnableVertexAttribArray(location);
                }
            }
        }
    }

    OglIndexBuffer* ibo = dynamic_cast<OglIndexBuffer*>(mGeometry->GetIndexBuffer());

    if (ibo)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->GetId());
        glDrawElements(GL_TRIANGLES, primCount * 3, GL_UNSIGNED_INT, reinterpret_cast<void*>(start));
    }
}

void OglGraphicsDevice::SetTexture(uint index, ITexture2D* tex)
{
    mTextures[index] = dynamic_cast<OglTexture2D*>(tex);
}

}

