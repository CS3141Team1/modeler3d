#pragma once

#include "IGraphicsResource.h"
#include "IIndexBuffer.h"
#include "IVertexBuffer.h"
#include "Types.h"

namespace Video
{

/**
 * Holds vertex buffers and an index buffer
 *
 * @author Nicholas Hamilton
 */
class IGeometry : public IGraphicsResource
{
public:
    virtual ~IGeometry() {}

    /**
     * @return Total number of vertex buffers in the geometry
     */
    virtual uint GetVertexBufferCount() const = 0;

    /**
     * @return Vertex buffer at a given index
     */
    virtual const IVertexBuffer* GetVertexBuffer(uint index) const = 0;

    /**
     * @return Vertex buffer at a given index
     */
    virtual IVertexBuffer* GetVertexBuffer(uint index) = 0;

    /**
     * @return Index buffer if it exists
     */
    virtual const IIndexBuffer* GetIndexBuffer() const = 0;

    /**
     * @return Index buffer if it exists
     */
    virtual IIndexBuffer* GetIndexBuffer() = 0;

    /**
     * Set the vertex buffer of the geometry
     */
    virtual void SetVertexBuffer(IVertexBuffer* vbo) = 0;

    /**
     * Set the vertex buffers of the geometry
     */
    virtual void SetVertexBuffers(IVertexBuffer** vbos, uint count) = 0;

    /**
     * Set the index buffer of the geometry
     */
    virtual void SetIndexBuffer(IIndexBuffer* ibo) = 0;
};

}
