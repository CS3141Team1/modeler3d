#pragma once

#include "ITexture.h"
#include "Types.h"

namespace Video
{

/**
 * Interface for 2D drawing
 *
 * @author Nicholas Hamilton
 */
class IRenderer2D
{
public:
    virtual ~IRenderer2D() {}

    /**
     * Set the tint that will be used for the renderer.
     * Color components should be normalized.
     */
    virtual void SetColor(float32 r, float32 g, float32 b, float32 a = 1.0f) = 0;

    /**
     * Set the texture to draw with.
     * If it is null, no texture will be used.
     */
    virtual void SetTexture(ITexture2D* texture) = 0;

    /**
     * Draws a rectangle to the screen.
     * Parameters are in pixels.
     */
    virtual void FillRect(float32 x, float32 y, float32 w, float32 h) = 0;

};

}
