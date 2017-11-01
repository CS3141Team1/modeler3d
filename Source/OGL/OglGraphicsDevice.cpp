#include "OGL/OglGraphicsDevice.h"

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include <GL/glew.h>
#include <GL/glu.h>

#include "Math/ModelerMath.h"
#include "Math/Matrix4.h"

#include "SDL2/Sdl2Window.h"

#include "OGL/OglGeometry.h"
#include "OGL/OglIndexBuffer.h"
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
    : mWindow(window)
{
}

OglGraphicsDevice::~OglGraphicsDevice()
{
}

void OglGraphicsDevice::Init()
{
    glEnable(GL_DEPTH_TEST);
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

    // TODO real aspect ratio
    Matrix4f projection = Matrix4f::ToPerspective(Math::ToRadians(70.0f), Ratio, 0.1f, 1000.0f);
    Matrix4f view = Matrix4f::ToLookAt(Vector3f(0, 1, 2), Vector3f::Zero, Vector3f::Up);
    Matrix4f model = Matrix4f::ToYaw(Angle) * Matrix4f::ToPitch(Angle * 1.3) * Matrix4f::ToRoll(Angle * 1.7) * Matrix4f::ToTranslation(Vector3f(0.2, -0.8, 0));
    Matrix3f normalMat(Inverse(Transpose(model)));

//    cout << "Matrices" << endl;
//    cout << projection << endl << endl;
//    cout << view << endl << endl;
//    cout << model << endl << endl;

    glUniformMatrix4fv(glGetUniformLocation(mShader->GetId(), "Projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(mShader->GetId(), "View"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(mShader->GetId(), "Model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(mShader->GetId(), "NormalMat"), 1, GL_FALSE, &normalMat[0][0]);

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
                    cout << "Found " << name << ": " << elem.Count << ", " << format.GetOffsetOf(j) << ", " << format.GetSizeInBytes() << ", " << glGetAttribLocation(mShader->GetId(), name.c_str()) << endl;

                    glVertexAttribPointer(
                            glGetAttribLocation(mShader->GetId(), name.c_str()),
                            elem.Count,
                            GL_FLOAT,
                            GL_FALSE,
                            format.GetSizeInBytes(),
                            reinterpret_cast<void*>(format.GetOffsetOf(j))
                    );
                    GLint location = glGetAttribLocation(mShader->GetId(), name.c_str());
                    cout << location << " ";
                    glEnableVertexAttribArray(location);
                }
            }
        }
    }
    cout << endl;

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

void OglGraphicsDevice::DrawIndices(Primitive prim, uint start, uint primCount)
{
    if (mGeometry == nullptr) return;
    if (mShader == nullptr) return;

    // bind current shader
    glUseProgram(mShader->GetId());

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

}
