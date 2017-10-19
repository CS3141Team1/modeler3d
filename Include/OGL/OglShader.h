#pragma once

#include <GL/glew.h>

#include "IShader.h"

namespace Video
{

class OglShader : public IShader
{
public:
    OglShader(const std::string& vs, const std::string& fs);
    ~OglShader();

    void Release();

    GLuint GetId() const { return mId; }

    const std::string& GetVertexSource() const { return mVertexSource; }
    const std::string& GetFragmentSource() const { return mFragmentSource; }

private:
    GLuint CompileShader(const std::string& source, GLenum type, const std::string& typeName);
    bool LinkProgram(GLuint vertex, GLuint fragment);

    GLuint mId = 0;
    std::string mVertexSource;
    std::string mFragmentSource;
};

}
