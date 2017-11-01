#pragma once

#include "IGeometry.h"
#include "IShader.h"
#include "IVertexBuffer.h"
#include "Types.h"

namespace Video
{

/**
 * Type of shape to draw
 *
 * @author Nicholas Hamilton
 */
enum class Primitive
{
    TriangleList
};

/**
 * Type of buffer
 *
 * @author Nicholas Hamilton
 */
enum class BufferHint
{
    /** Send to the GPU once */
    Static,
    /** Send to the GPU sometimes */
    Dynamic,
    /** Send to the GPU every frame */
    Stream
};

/**
 * Base interface for graphics
 *
 * @author Nicholas Hamilton
 */
class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    /**
     * @return Vertex buffer created by the device
     *
     * @param count Number of vertices in the buffer
     */
    virtual IVertexBuffer* CreateVertexBuffer(VertexFormat format, uint count, BufferHint hint = BufferHint::Dynamic) = 0;

    /**
     * @return Shader created by the device
     *
     * @param vertex GLSL vertex shader source code
     * @param fragment GLSL fragment shader source code
     */
    virtual IShader* CreateShader(const std::string& vertex, const std::string& fragment) = 0;

    /**
     * @return geometry created by the device
     */
    virtual IGeometry* CreateGeometry() = 0;

    /**
     * Sets the color that the screen should be when being cleared.
     * values should be between 0 and 1.
     */
    virtual void SetClearColor(float32 r, float32 g, float32 b, float32 a = 1.0) = 0;

    /**
     * Clears the buffers of the current render target (default is screen)
     */
    virtual void Clear(bool color = true, bool depth = true) = 0;

    /**
     * @return Current geometry
     */
    virtual const IGeometry* GetGeometry() const = 0;

    /**
     * @return Current geometry
     */
    virtual IGeometry* GetGeometry() = 0;

    /**
     * @return Current shader
     */
    virtual const IShader* GetShader() const = 0;

    /**
     * @return Current shader
     */
    virtual IShader* GetShader() = 0;

    /**
     * Set the current geometry
     */
    virtual void SetGeometry(IGeometry* geom) = 0;

    /**
     * Set the current shader
     */
    virtual void SetShader(IShader* shader) = 0;

    /**
     * Draw the current geometry with the set shader
     *
     * @param prim Primitive type to draw
     * @param start Index of first vertex to draw
     * @param primCount Number of primitives to draw, NOT number of vertices
     */
    virtual void Draw(Primitive prim, uint start, uint primCount) = 0;
};

}
