#pragma once

#include "Types.h"

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

    virtual ~ITexture() {}

    virtual void Release() = 0;
    virtual bool IsReleased() const = 0;

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

    virtual WrapMode GetWrapModeS() const = 0;
    virtual WrapMode GetWrapModeT() const = 0;

    virtual void SetWrapModeS(WrapMode s) = 0;
    virtual void SetWrapModeT(WrapMode t) = 0;
    virtual void SetWrapModes(WrapMode s, WrapMode t)
    {
        SetWrapModeS(s);
        SetWrapModeT(t);
    }

    virtual uint GetWidth() const = 0;
    virtual uint GetHeight() const = 0;

    virtual void SetPixels(void* data, uint x, uint y, uint width, uint height) = 0;
};

}
