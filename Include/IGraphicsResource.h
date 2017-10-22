#pragma once

namespace Video
{

/**
 * Interface for all resources created by a graphics device
 *
 * @author Nicholas Hamilton
 */
class IGraphicsResource
{
public:
    virtual ~IGraphicsResource() {}

    /**
     * Release any GPU data
     */
    virtual void Release() = 0;
};

}
