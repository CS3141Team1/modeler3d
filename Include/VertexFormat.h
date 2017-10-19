#pragma once

#include <string>
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
    UInt8,
    UInt16,
    UInt32,
    Float32
};

static uint SizeInBytes(DataType type)
{
    switch (type)
    {
    case DataType::UInt8:
        return 1;
    case DataType::UInt16:
        return 2;
    case DataType::UInt32:
    case DataType::Float32:
        return 4;
    default:
        return 0;
    }
}

struct VertexElement
{
    Attribute Attrib;
    uint Count;
    DataType Type;

    VertexElement(Attribute attrib, uint count, DataType type = DataType::Float32)
        : Attrib(attrib),
          Count(count),
          Type(type) {}

    uint GetSizeInBytes() const { return Video::SizeInBytes(Type) * Count; }
};

class VertexFormat
{
public:
    static const VertexFormat Position3fTexCoord02fColor4f;
    static const VertexFormat Position3fNormal3fColor4f;
    static const VertexFormat Position3fNormal3fTexCoord02fColor4f;

    VertexFormat() : mElems(), mBytes(0) {}

    uint GetSizeInBytes() const { return mBytes; }
    uint GetElementCount() const { return mElems.size(); }
    const VertexElement& GetElement(uint index) const { return mElems[index]; }
    const VertexElement& operator[](uint index) const { return GetElement(index); }

    uint GetOffsetOf(uint index) const
    {
        uint total = 0;
        for (uint i = 0; i < index; i++)
        {
            total += GetElement(i).GetSizeInBytes();
        }
        return total;
    }

    VertexFormat& AddElement(VertexElement elem)
    {
        mElems.push_back(elem);
        mBytes += elem.GetSizeInBytes();
        return *this;
    }
    VertexFormat& AddElement(Attribute attrib, uint count, DataType type = DataType::Float32)
    {
        return AddElement(VertexElement(attrib, count, type));
    }
private:
    std::vector<VertexElement> mElems;
    uint mBytes;
};

}
