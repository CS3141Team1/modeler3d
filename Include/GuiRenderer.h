#pragma once

#include "IGraphicsDevice.h"
#include "Types.h"

#include "Math/ModelerMath.h"

namespace Video
{

/**
 * Interface for 2D drawing
 *
 * @author Nicholas Hamilton
 */
class GuiRenderer
{
public:
    GuiRenderer(IGraphicsDevice* gd);
    ~GuiRenderer();

    void Release();

    /**
     * Set the tint that will be used for the renderer.
     * Color components should be normalized.
     */
    void SetColor(float32 r, float32 g, float32 b, float32 a = 1.0f);

    /**
     * Draws a rectangle to the screen.
     * Parameters are in pixels.
     */
    void FillRect(float32 x, float32 y, float32 w, float32 h);

private:
    IGraphicsDevice* mGraphics;
    IShader* mShader;
    IGeometry* mGeometry;
    IIndexBuffer* mIndices;
    IVertexBuffer* mVertices;
    Core::Math::Vector4f mColor;
};

}
