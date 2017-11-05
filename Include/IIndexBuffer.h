#pragma once

#include "IGraphicsResource.h"
#include "Types.h"

namespace Video
{

/**
 * Interface for a index buffer
 *
 * @author Nicholas Hamilton
 */
class IIndexBuffer : public IGraphicsResource
{
public:
    static const uint BytesPerIndex = 4;

    virtual ~IIndexBuffer() {}

    /**
     * @return number of indices in the buffer
     */
    virtual uint GetLength() const = 0;

    /**
     * @return number of bytes the buffer uses
     */
    virtual uint GetSizeInBytes() const { return GetLength() * BytesPerIndex; }

    /**
     * @param out location to put the data
     */
    virtual void GetData(uint32* out, uint start, uint count) const = 0;

    /**
     * @param in location of data to set
     */
    virtual void SetData(const uint32* in, uint start, uint count) = 0;
};

}
