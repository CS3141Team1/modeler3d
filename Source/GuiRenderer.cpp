#include "GuiRenderer.h"

#include <string>

using namespace std;
using namespace Core::Math;

namespace Video
{

static const VertexFormat Format = VertexFormat()
        .AddElement(Attribute::Position, 2)
        .AddElement(Attribute::Color, 4)
        .AddElement(Attribute::TexCoord0, 2);

static const string VertexSource = ""
        "#version 120 \n"
        "attribute vec2 aPosition; \n"
        "attribute vec4 aColor; \n"
        "attribute vec2 aTexCoord0; \n"
        "varying vec4 vColor; \n"
        "varying vec2 vTexCoord0; \n"
        "void main() { \n"
        "   vColor = aColor; \n"
        "   vTexCoord0 = aTexCoord0; \n"
        "   gl_Position = vec4(aPosition, -1.0, 1.0); \n"
        "} \n";
static const string FragmentSource = ""
        "#version 120 \n"
        "varying vec4 vColor; \n"
        "varying vec2 vTexCoord0; \n"
        "uniform sampler2D Texture; "
        "uniform int HasTexture; "
        "void main() { \n"
        "   if (HasTexture == 1) { \n"
        "       gl_FragColor = vColor * texture2D(Texture, vTexCoord0); \n"
        "   } \n"
        "   else { \n"
        "       gl_FragColor = vColor; \n"
        "   } \n"
        "} \n";

GuiRenderer::GuiRenderer(IGraphicsDevice* gd)
    : mGraphics(gd),
      mShader(nullptr),
      mGeometry(nullptr),
      mVertices(nullptr),
      mTexture(nullptr),
      mFontTex(nullptr),
      mColor(0),
      mTranslate(0)
{
    mVertices = mGraphics->CreateVertexBuffer(Format, 4, BufferHint::Stream);
    mIndices = mGraphics->CreateIndexBuffer(6, BufferHint::Static);
    mGeometry = mGraphics->CreateGeometry();
    mShader = mGraphics->CreateShader(VertexSource, FragmentSource);
    mFontTex = mGraphics->CreateTexture2D("Assets/font.png");

    mGeometry->SetVertexBuffer(mVertices);
    mGeometry->SetIndexBuffer(mIndices);

    uint inds[] = {0, 1, 3, 0, 3, 2};
    mIndices->SetData(inds, 0, 6);
}

GuiRenderer::~GuiRenderer()
{
}

void GuiRenderer::Release()
{
    mGeometry->SetIndexBuffer(nullptr);
    mGeometry->SetVertexBuffer(nullptr);
    mGeometry->Release();
    mVertices->Release();
    mIndices->Release();
    mShader->Release();
}

void GuiRenderer::DrawText(const std::string& str, float32 size, float32 x, float32 y, float32 xWeight, float32 yWeight)
{
    // TODO FINISH
}

void GuiRenderer::SetColor(float32 r, float32 g, float32 b, float32 a)
{
    mColor = Vector4f(r, g, b, a);
}

void GuiRenderer::FillRect(float32 x, float32 y, float32 w, float32 h, float32 u, float32 v, float32 uWidth, float32 vHeight)
{
    const uint size = 8;
    float32 verts[size * 4];

    float32 width = mGraphics->GetWidth();
    float32 height = mGraphics->GetHeight();

    x = (mTranslate.X + x) * 2.0 / width - 1.0;
    y = (mTranslate.Y + y) * 2.0 / height - 1.0;
    w = w * 2.0 / width;
    h = h * 2.0 / height;

    uint index = 0;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            verts[index++] = x + i * w;
            verts[index++] = y + j * h;
            verts[index++] = mColor.R;
            verts[index++] = mColor.G;
            verts[index++] = mColor.B;
            verts[index++] = mColor.A;
            verts[index++] = u + i * uWidth;
            verts[index++] = v + j * vHeight;
        }
    }

    mVertices->SetData(verts, 0, 4);

    mShader->SetInt32("HasTexture", mTexture != nullptr);
    mShader->SetInt32("Texture", 0);
    mGraphics->SetTexture(0, mTexture);

    mGraphics->SetShader(mShader);
    mGraphics->SetGeometry(mGeometry);
    mGraphics->DrawIndices(Primitive::TriangleList, 0, 2);
}

void GuiRenderer::SetTexture(ITexture2D* texture)
{
    mTexture = texture;
}

}
