#pragma once

#include "IGraphicsResource.h"
#include "Types.h"

namespace Video
{

/**
 * Interface for a 2D texture
 *
 * @author Nicholas Hamilton
 */
class ITexture2D : public IGraphicsResource
{
public:
    virtual ~ITexture2D() {}

    /**
     * @return width of texture in pixels
     */
    virtual uint GetWidth() const = 0;

    /**
     * @return height of texture in pixels
     */
    virtual uint GetHeight() const = 0;

    /**
     * get RGBA data from the texture from the pixels (x,y) to (x+w,y+h) in row-major order
     */
    virtual void GetData(uint8* out, uint x, uint y, uint w, uint h) const = 0;

    /**
     * set RGBA data to the texture from the pixels (x,y) to (x+w,y+h) in row-major order
     */
    virtual void SetData(const uint8* in, uint x, uint y, uint w, uint h) = 0;
};

}
