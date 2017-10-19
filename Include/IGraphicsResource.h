#pragma once

namespace Video
{

class IGraphicsResource
{
public:
    virtual ~IGraphicsResource() {}

    virtual void Release() = 0;
};

}
