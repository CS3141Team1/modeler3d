#pragma once

namespace Video
{

class ITexture
{
public:
    enum class Format
    {
        Color,
        ColorSrgb,
        Color32,
        Depth
    };

    enum class MagFilter
    {
        Nearest,
        Linear
    };

    enum class MinFilter
    {
        Nearest,
        NearestMipmapNearest,
        NearestMipmapLinear,
        Linear,
        LinearMipmapNearest,
        LinearMipmapLinear
    };

    enum class WrapMode
    {
        ClampToEdge,
        Repeat
    };

    virtual ~ITexture()
    {
        Release();
    }

    virtual void Release() = 0;

    virtual Format GetFormat() const = 0;

    virtual MagFilter GetMagFilter() const = 0;
    virtual MinFilter GetMinFilter() const = 0;

    virtual void SetMagFilter(MagFilter mag) = 0;
    virtual void SetMinFilter(MinFilter min) = 0;
    virtual void SetFilters(MagFilter mag, MinFilter min)
    {
        SetMagFilter(mag);
        SetMinFilter(min);
    }
};

class ITexture2D : public ITexture
{
public:
    virtual ~ITexture2D() {}
};

}
