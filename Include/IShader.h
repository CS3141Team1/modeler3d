#pragma once

#include <string>

#include "Math/ModelerMath.h"

#include "IGraphicsResource.h"

namespace Video
{

/**
 * Interface for a shader
 *
 * @author Nicholas Hamilton
 */
class IShader : public IGraphicsResource
{
public:
    virtual ~IShader() {}

    /**
     * @return source code used for the vertex shader
     */
    virtual const std::string& GetVertexSource() const = 0;

    /**
     * @return source code used for the fragment shader
     */
    virtual const std::string& GetFragmentSource() const = 0;

    /**
     * Set a 4x4 matrix uniform
     */
    virtual void SetMatrix4f(const std::string& name, const Core::Math::Matrix4f& mat) = 0;

    /**
     * Set a 3x3 matrix uniform
     */
    virtual void SetMatrix3f(const std::string& name, const Core::Math::Matrix3f& mat) = 0;

    /**
     * Set a 4-vector uniform
     */
    virtual void SetVector4f(const std::string& name, const Core::Math::Vector4f& vec) = 0;

    /**
     * Set a 3-vector uniform
     */
    virtual void SetVector3f(const std::string& name, const Core::Math::Vector3f& vec) = 0;

    /**
     * Set a 2-vector uniform
     */
    virtual void SetVector2f(const std::string& name, const Core::Math::Vector2f& vec) = 0;

    /**
     * Set a float uniform
     */
    virtual void SetFloat32(const std::string& name, float32 f) = 0;

    /**
     * Set an integer uniform
     */
    virtual void SetInt32(const std::string& name, int32 i) = 0;
};

}
