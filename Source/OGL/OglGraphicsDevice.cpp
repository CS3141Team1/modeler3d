#include "OGL/OglGraphicsDevice.h"

#include <cmath>
#include <iostream>
#include <string>
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

namespace Video
{

OglGraphicsDevice::OglGraphicsDevice()
{
}

OglGraphicsDevice::~OglGraphicsDevice()
{
}

void OglGraphicsDevice::Init()
{

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

void OglGraphicsDevice::Draw(Primitive prim, uint start, uint primCount)
{
    if (mGeometry == nullptr) return;
    if (mShader == nullptr) return;

    // bind current shader
    glUseProgram(mShader->GetId());

    // TODO real aspect ratio
    Matrix4f projection = Math::Matrix4f::ToPerspective(Math::ToRadians(70.0f), 1.3333f, 0.1f, 1000.0f);
    Matrix4f view = Math::Matrix4f::ToLookAt(Vector3f(0, 1, -5), Vector3f::Zero, Vector3f::Up);
    Matrix4f model = Matrix4f::Identity;
    Matrix3f normalMat(model);

    glUniformMatrix4fv(glGetUniformLocation(mShader->GetId(), "Projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(mShader->GetId(), "View"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(mShader->GetId(), "Model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(mShader->GetId(), "NormalMat"), 1, GL_FALSE, &normalMat[0][0]);

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
