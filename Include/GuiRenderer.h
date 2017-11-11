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
     * Call at beginning of frame
     */
    void Reset()
    {
        SetColor(0, 0, 0);
        mTranslate = 0;
    }

    /**
     * Set an offset to render from
     */
    void Translate(float32 x, float32 y) { mTranslate += Core::Math::Vector2f(x, y); }

    /**
     * Set the tint that will be used for the renderer.
     * Color components should be normalized.
     */
    void SetColor(float32 r, float32 g, float32 b, float32 a = 1.0f);

    void SetColor(const Core::Math::Vector3f& r) { SetColor(r.R, r.G, r.B); }
    void SetColor(const Core::Math::Vector4f& r) { SetColor(r.R, r.G, r.B, r.A); }

    void SetTexture(ITexture2D* texture);

    /**
     * Draws a rectangle to the screen.
     * Parameters are in pixels.
     */
    void FillRect(float32 x, float32 y, float32 w, float32 h, float32 u = 0, float32 v = 0, float32 uWidth = 1, float32 vHeight = 1);

private:
    IGraphicsDevice* mGraphics;
    IShader* mShader;
    IGeometry* mGeometry;
    IIndexBuffer* mIndices;
    IVertexBuffer* mVertices;
    ITexture2D* mTexture;
    Core::Math::Vector4f mColor;
    Core::Math::Vector2f mTranslate;
};

}
