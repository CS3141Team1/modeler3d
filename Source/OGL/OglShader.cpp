#include "OGL/OglShader.h"

using namespace std;

namespace Video
{

OglShader::OglShader(const string& vs, const string& fs)
    : mVertexSource(vs),
      mFragmentSource(fs)
{

}

OglShader::~OglShader()
{
    Release();
}

void OglShader::Release()
{
    if (mId != 0)
    {
        glDeleteProgram(mId);
        mId = 0;
    }
}

GLuint OglShader::CompileShader(const std::string& source, GLenum type,
        const std::string& typeName)
{
    const GLchar* sources[] = { source.c_str() };

    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, sources, NULL);



    return id;
}

bool OglShader::LinkProgram(GLuint vertex, GLuint fragment)
{
    // TODO finish
    return false;
}

}
