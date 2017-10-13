#pragma once

#include <string>

namespace Video
{

class IShader
{
public:
    virtual ~IShader() {}

    virtual void Release() = 0;
    virtual bool IsReleased() const = 0;

    virtual const std::string& GetVertexSource() const = 0;
    virtual const std::string& GetFragmentSource() const = 0;
};

}
