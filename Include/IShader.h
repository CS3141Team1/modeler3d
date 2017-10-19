#pragma once

#include <string>

#include "IGraphicsResource.h"

namespace Video
{

class IShader : public IGraphicsResource
{
public:
    virtual ~IShader() {}

    virtual const std::string& GetVertexSource() const = 0;
    virtual const std::string& GetFragmentSource() const = 0;


};

}
