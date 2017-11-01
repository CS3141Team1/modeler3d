#pragma once

#include <string>

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
};

}
