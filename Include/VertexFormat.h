#pragma once

#include <string>
#include <vector>

#include "Types.h"

namespace Video
{

/**
 * Vertex attributes
 */
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

/**
 * Vertex data types
 *
 * @author Nicholas Hamilton
 */
enum class DataType
{
    UInt8,
    UInt16,
    UInt32,
    Float32
};

/**
 * @return size of a data type in bytes
 *
 * @author Nicholas Hamilton
 */
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

/**
 * Piece of a vertex format
 *
 * @author Nicholas Hamilton
 */
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

/**
 * Collection of vertex elements
 *
 * @author Nicholas Hamilton
 */
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

    /**
     * @return byte offset of an element
     */
    uint GetOffsetOf(uint index) const
    {
        uint total = 0;
        for (uint i = 0; i < index; i++)
        {
            total += GetElement(i).GetSizeInBytes();
        }
        return total;
    }

    /**
     * Add an element to this format
     *
     * @return self, for easy chaining
     */
    VertexFormat& AddElement(VertexElement elem)
    {
        mElems.push_back(elem);
        mBytes += elem.GetSizeInBytes();
        return *this;
    }

    /**
     * Add properties of an element
     *
     * @return self, for easy chaining
     */
    VertexFormat& AddElement(Attribute attrib, uint count, DataType type = DataType::Float32)
    {
        return AddElement(VertexElement(attrib, count, type));
    }
private:
    std::vector<VertexElement> mElems;
    uint mBytes;
};

}
