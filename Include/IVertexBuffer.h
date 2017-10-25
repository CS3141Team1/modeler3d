#pragma once

#include "IGraphicsResource.h"
#include "Types.h"
#include "VertexFormat.h"

namespace Video
{

/**
 * Interface for a vertex buffer
 *
 * @author Nicholas Hamilton
 */
class IVertexBuffer : public IGraphicsResource
{
public:
    virtual ~IVertexBuffer() {}

    /**
     * @return format used for the buffer
     */
    virtual const VertexFormat& GetFormat() const = 0;

    /**
     * @return number of vertices in the buffer
     */
    virtual uint GetLength() const = 0;

    /**
     * @return number of bytes the buffer uses
     */
    virtual uint GetSizeInBytes() const { return GetLength() * GetFormat().GetSizeInBytes(); }

    /**
     * @param out location to put the data
     */
    virtual void GetData(float* out, uint start, uint count) const = 0;

    /**
     * @param in location of data to set
     */
    virtual void SetData(float* in, uint start, uint count) = 0;
};

}
