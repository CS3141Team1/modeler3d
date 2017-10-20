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
#include "OGL/OglGeometry.h"
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

OglGraphicsDevice::OglGraphicsDevice()
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

IVertexBuffer* OglGraphicsDevice::CreateVertexBuffer(VertexFormat format,
        uint count, BufferHint hint)
{
    OglVertexBuffer* vbo = new OglVertexBuffer(format, count); //, hint);
    return vbo;
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
//            cout << "VBO: " << vbo->GetId() << endl;

//            vector<GLfloat> floats(6 * 3);
//            glGetBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 6 * 3, &floats[0]);
//            for (uint i = 0; i < floats.size(); i++)
//            {
//                cout << floats[i] << " ";
//            }
//            cout << endl;

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

    glDrawArrays(GL_TRIANGLES, start, primCount * 3);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(70.0, 4.0 / 3.0, 0.1, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, -2.0f);
//
//    glEnable(GL_COLOR);
//
//    glBegin(GL_TRIANGLES);
//        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//        glVertex3f(-0.5f, -0.5f, 0.0);
//        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
//        glVertex3f( 0.5f, -0.5f, 0.0);
//        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
//        glVertex3f( 0.0f,  0.5f, 0.0);
//    glEnd();
}

}
