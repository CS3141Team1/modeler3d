#include "OGL/OglGraphicsDevice.h"

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/glu.h>

#include "Math/ModelerMath.h"
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
    cout << "Geometry: " << mGeometry << endl;
}

IShader* OglGraphicsDevice::CreateShader(const std::string& vertex,
        const std::string& fragment)
{
    return new OglShader(vertex, fragment);
}

void OglGraphicsDevice::SetShader(IShader* shader)
{
    mShader = dynamic_cast<OglShader*>(shader);
    cout << "Shader: " << mShader << endl;
}

void OglGraphicsDevice::Draw(Primitive prim, uint start, uint primCount)
{
    if (mGeometry == nullptr) return;
    if (mShader == nullptr) return;

    // bind current shader
    glUseProgram(mShader->GetId());

//    Matrix4f projection;

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
