#include "OGL/OglShader.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace Core::Math;

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

void OglShader::SetMatrix4f(const std::string& name, const Matrix4f& mat)
{
    glUseProgram(mId);
    glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void OglShader::SetMatrix3f(const std::string& name, const Matrix3f& mat)
{
    glUseProgram(mId);
    glUniformMatrix3fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void OglShader::SetVector4f(const std::string& name, const Vector4f& vec)
{
    glUseProgram(mId);
    glUniform4fv(glGetUniformLocation(mId, name.c_str()), 1, &vec[0]);
}

void OglShader::SetVector3f(const std::string& name, const Vector3f& vec)
{
    glUseProgram(mId);
    glUniform3fv(glGetUniformLocation(mId, name.c_str()), 1, &vec[0]);
}

void OglShader::SetVector2f(const std::string& name, const Vector2f& vec)
{
    glUseProgram(mId);
    glUniform2fv(glGetUniformLocation(mId, name.c_str()), 1, &vec[0]);
}

void OglShader::SetFloat32(const std::string& name, float32 f)
{
    glUseProgram(mId);
    glUniform1f(glGetUniformLocation(mId, name.c_str()), f);
}

void OglShader::SetInt32(const std::string& name, int32 i)
{
    glUseProgram(mId);
    glUniform1i(glGetUniformLocation(mId, name.c_str()), i);
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
