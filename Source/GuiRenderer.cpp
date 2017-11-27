#include "GuiRenderer.h"

#include <string>
#include <unordered_map>

using namespace std;
using namespace Core::Math;

namespace Video
{

static const float32 CharRatio = 15.0f / 16.0f; //33.0f / 55.5f;
static const float32 CharWidth = 1.0f / 16.0f; //16.0f / 256.0f; //33.0f / 532.0f;
static const float32 CharHeight = 1.0f / 16.0f; //16.0f / 240.0f; //55.5f / 288.0f;

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
        { 'A', { 1, 4 } },
        { 'B', { 2, 4 } },
        { 'C', { 3, 4 } },
        { 'D', { 4, 4 } },
        { 'E', { 5, 4 } },
        { 'F', { 6, 4 } },
        { 'G', { 7, 4 } },
        { 'H', { 8, 4 } },
        { 'I', { 9, 4 } },
        { 'J', { 10, 4 } },
        { 'K', { 11, 4 } },
        { 'L', { 12, 4 } },
        { 'M', { 13, 4 } },
        { 'N', { 14, 4 } },
        { 'O', { 15, 4 } },
        { 'P', { 0, 5 } },
        { 'Q', { 1, 5 } },
        { 'R', { 2, 5 } },
        { 'S', { 3, 5 } },
        { 'T', { 4, 5 } },
        { 'U', { 5, 5 } },
        { 'V', { 6, 5 } },
        { 'W', { 7, 5 } },
        { 'X', { 8, 5 } },
        { 'Y', { 9, 5 } },
        { 'Z', { 10, 5 } },
        { 'a', { 1, 6 } },
        { 'b', { 2, 6 } },
        { 'c', { 3, 6 } },
        { 'd', { 4, 6 } },
        { 'e', { 5, 6 } },
        { 'f', { 6, 6 } },
        { 'g', { 7, 6 } },
        { 'h', { 8, 6 } },
        { 'i', { 9, 6 } },
        { 'j', { 10, 6 } },
        { 'k', { 11, 6 } },
        { 'l', { 12, 6 } },
        { 'm', { 13, 6 } },
        { 'n', { 14, 6 } },
        { 'o', { 15, 6 } },
        { 'p', { 0, 7 } },
        { 'q', { 1, 7 } },
        { 'r', { 2, 7 } },
        { 's', { 3, 7 } },
        { 't', { 4, 7 } },
        { 'u', { 5, 7 } },
        { 'v', { 6, 7 } },
        { 'w', { 7, 7 } },
        { 'x', { 8, 7 } },
        { 'y', { 9, 7 } },
        { 'z', { 10, 7 } },
        { '1', { 1, 3 } },
        { '2', { 2, 3 } },
        { '3', { 3, 3 } },
        { '4', { 4, 3 } },
        { '5', { 5, 3 } },
        { '6', { 6, 3 } },
        { '7', { 7, 3 } },
        { '8', { 8, 3 } },
        { '9', { 9, 3 } },
        { '0', { 0, 3 } },
        { '.', { 14, 2 } },
        { ',', { 12, 2 } },
        { '!', { 1, 2 } },
        { '?', { 15, 3 } },
        { '(', { 8, 2 } },
        { ')', { 9, 2 } },
        { '+', { 11, 2 } },
        { '-', { 13, 2 } }
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
    mFontTex = mGraphics->CreateTexture2D("Assets/font_new.png");

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
    float32 scale = 10.0f / 16.0f;

    float32 totalWidth = scale * str.size() * size * CharRatio;
    float32 charWidth = size * CharRatio;

    float32 posX = x - xWeight * totalWidth;
    float32 posY = y - yWeight * size;

    ITexture2D* tmp = mTexture;
    SetTexture(mFontTex);

    for (uint i = 0; i < str.size(); i++)
    {
        char c = str[i];
        CharPosition p = CharMap[c];
        FillRect(posX, posY, charWidth, size, p.X * CharWidth, 1 - (p.Y + 1) * CharHeight, CharWidth - 1.0f / 256.0f, CharHeight - 1.0f / 240.0f); //p.X * CharWidth, 1 - (p.Y + 1) * CharHeight, CharWidth, CharHeight);
        posX += charWidth * scale;
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
