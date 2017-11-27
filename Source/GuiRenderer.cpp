#include "GuiRenderer.h"

#include <string>
#include <unordered_map>

using namespace std;
using namespace Core::Math;

namespace Video
{

static const float32 CharRatio = 33.0f / 55.5f;
static const float32 CharWidth = 33.0f / 532.0f;
static const float32 CharHeight = 55.5f / 288.0f;

static const VertexFormat Format = VertexFormat()
        .AddElement(Attribute::Position, 2)
        .AddElement(Attribute::Color, 4)
        .AddElement(Attribute::TexCoord0, 2);

struct CharPosition
{
    int32 X, Y;

    CharPosition() : X(-1), Y(-1) {}
    CharPosition(int32 x, int32 y) : X(x), Y(y) {}
};

static unordered_map<char, CharPosition> CharMap =
{
        { 'A', { 0, 0 } },
        { 'B', { 1, 0 } },
        { 'C', { 2, 0 } },
        { 'D', { 3, 0 } },
        { 'E', { 4, 0 } },
        { 'F', { 5, 0 } },
        { 'G', { 6, 0 } },
        { 'H', { 7, 0 } },
        { 'I', { 8, 0 } },
        { 'J', { 9, 0 } },
        { 'K', { 10, 0 } },
        { 'L', { 11, 0 } },
        { 'M', { 12, 0 } },
        { 'N', { 13, 0 } },
        { 'O', { 14, 0 } },
        { 'P', { 15, 0 } },
        { 'Q', { 0, 1 } },
        { 'R', { 1, 1 } },
        { 'S', { 2, 1 } },
        { 'T', { 3, 1 } },
        { 'U', { 4, 1 } },
        { 'V', { 5, 1 } },
        { 'W', { 6, 1 } },
        { 'X', { 7, 1 } },
        { 'Y', { 8, 1 } },
        { 'Z', { 9, 1 } },
        { 'a', { 0, 2 } },
        { 'b', { 1, 2 } },
        { 'c', { 2, 2 } },
        { 'd', { 3, 2 } },
        { 'e', { 4, 2 } },
        { 'f', { 5, 2 } },
        { 'g', { 6, 2 } },
        { 'h', { 7, 2 } },
        { 'i', { 8, 2 } },
        { 'j', { 9, 2 } },
        { 'k', { 10, 2 } },
        { 'l', { 11, 2 } },
        { 'm', { 12, 2 } },
        { 'n', { 13, 2 } },
        { 'o', { 14, 2 } },
        { 'p', { 15, 2 } },
        { 'q', { 0, 3 } },
        { 'r', { 1, 3 } },
        { 's', { 2, 3 } },
        { 't', { 3, 3 } },
        { 'u', { 4, 3 } },
        { 'v', { 5, 3 } },
        { 'w', { 6, 3 } },
        { 'x', { 7, 3 } },
        { 'y', { 8, 3 } },
        { 'z', { 9, 3 } },
        { '1', { 13, 3 } },
        { '2', { 14, 3 } },
        { '3', { 15, 3 } },
        { '4', { 0, 4 } },
        { '5', { 1, 4 } },
        { '6', { 2, 4 } },
        { '7', { 3, 4 } },
        { '8', { 4, 4 } },
        { '9', { 5, 4 } },
        { '0', { 6, 4 } },
        { '.', { 11, 4 } },
        { ',', { 12, 4 } },
        { '!', { 13, 4 } },
        { '?', { 14, 4 } },
        { '(', { 7, 4 } },
        { ')', { 15, 4 } },
};

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
    float32 totalWidth = str.size() * size * CharRatio;
    float32 charWidth = size * CharRatio;

    float32 posX = x - xWeight * totalWidth;
    float32 posY = y - yWeight * size;

    ITexture2D* tmp = mTexture;
    SetTexture(mFontTex);

    for (uint i = 0; i < str.size(); i++)
    {
        char c = str[i];
        CharPosition p = CharMap[c];
        FillRect(posX, posY, charWidth, size, p.X * CharWidth, 1 - (p.Y + 1) * CharHeight, CharWidth, CharHeight);
        posX += charWidth;
    }

    SetTexture(tmp);
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
