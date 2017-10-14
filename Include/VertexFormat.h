#pragma once

#include <vector>

#include "Types.h"

namespace Video
{

enum class Attribute
{
    Position,
    Normal,
    Color,
    TexCoord0,
    TexCoord1,
    TexCoord2,
    TexCoord3
};

enum class DataType
{
    Uint8,
    Int16,
    UInt16,
    Int32,
    UInt32,
    Float32,
};

struct VertexElement
{
    Attribute Attrib;
    uint Count;
    DataType Type;

    VertexElement(Attribute attrib, uint count, DataType type = DataType::Float32)
        : Attrib(attrib),
          Count(count),
          Type(type) {}
};

class VertexFormat
{
public:
    static const VertexFormat Position3fTexCoordZero2fColor4f;

    VertexFormat() : mElems(), mElemCount(0) {}

    ~VertexFormat()
    {
        delete[] mElems;
    }

    const uint GetElementCount() const { return mElemCount; }
    const VertexElement& GetElement(uint index) const { return mElems[index]; }
    const VertexElement& operator[](uint index) const { return GetElement(index); }

    VertexFormat& AddElement(VertexElement elem)
    {
        mElems.push_back(elem);
        return *this;
    }
    VertexFormat& AddElement(Attribute attrib, uint count, DataType type = DataType::Float32)
    {
        return AddElement(VertexElement(attrib, count, type));
    }
private:
    std::vector<VertexElement> mElems;
    uint mElemCount;
};

const VertexFormat VertexFormat::Position3fTexCoordZero2fColor4f = VertexFormat()
        .AddElement(Attribute::Position, 3)
        .AddElement(Attribute::TexCoord0, 2)
        .AddElement(Attribute::Color, 4);

}
