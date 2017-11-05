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

    void SetMatrix4f(const std::string& name, const Core::Math::Matrix4f& mat);
    void SetMatrix3f(const std::string& name, const Core::Math::Matrix3f& mat);
    void SetVector4f(const std::string& name, const Core::Math::Vector4f& vec);
    void SetVector3f(const std::string& name, const Core::Math::Vector3f& vec);
    void SetVector2f(const std::string& name, const Core::Math::Vector2f& vec);
    void SetFloat32(const std::string& name, float32 f);
    void SetInt32(const std::string& name, int32 i);
private:
    GLuint CompileShader(const std::string& source, GLenum type, const std::string& typeName);
    bool LinkProgram(GLuint vertex, GLuint fragment);

    GLuint mId = 0;
    std::string mVertexSource;
    std::string mFragmentSource;
};

}
