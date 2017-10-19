#include "OGL/OglShader.h"

#include <iostream>
#include <vector>

using namespace std;

namespace Video
{

OglShader::OglShader(const string& vs, const string& fs)
    : mVertexSource(vs),
      mFragmentSource(fs)
{
    cout << "Vertex: " << vs << endl;
    cout << "Fragment: " << fs << endl;

    mId = glCreateProgram();

    GLuint vert = 0, frag = 0;

    vert = CompileShader(vs, GL_VERTEX_SHADER, "Vertex Shader");
    frag = CompileShader(fs, GL_FRAGMENT_SHADER, "Fragment Shader");

    if (!(vert && frag && LinkProgram(vert, frag)))
    {
        cout << "Shader creation failed" << endl;
        Release();
    }
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
    glCompileShader(id);

    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);
        vector<GLchar> log(logSize);
        glGetShaderInfoLog(id, logSize, &logSize, &log[0]);
        cout << typeName << " Error: " << &log[0] << endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

bool OglShader::LinkProgram(GLuint vertex, GLuint fragment)
{
    glAttachShader(mId, vertex);
    glAttachShader(mId, fragment);
    glLinkProgram(mId);

    GLint linked = 0;
    glGetProgramiv(mId, GL_LINK_STATUS, &linked);

    if (linked == GL_FALSE)
    {
        GLint logLength = 0;
        glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &logLength);
        vector<GLchar> log(logLength);
        glGetProgramInfoLog(mId, logLength, &logLength, &log[0]);
        cout << "Program Link Error: " << logLength << &log[0] << endl;

        glDeleteProgram(mId);
        mId = 0;
        return false;
    }

//    glDetachShader(mId, vertex);
//    glDetachShader(mId, fragment);

    return true;
}

}
