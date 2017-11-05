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
 * Piece of a vertex format
 *
 * @author Nicholas Hamilton
 */
struct VertexElement
{
    Attribute Attrib;
    uint Count;

    VertexElement(Attribute attrib, uint count)
        : Attrib(attrib),
          Count(count) {}

    uint GetSizeInBytes() const { return 4 * Count; }
};

/**
 * Collection of vertex elements
 *
 * @author Nicholas Hamilton
 */
class VertexFormat
{
public:
    static const VertexFormat Position3TexCoord02Color4;
    static const VertexFormat Position3Normal3Color4;
    static const VertexFormat Position3Normal3TexCoord02Color4;

    VertexFormat() : mElems(), mBytes(0) {}

    uint GetSizeInBytes() const { return mBytes; }
    uint GetSizeInFloats() const { return mBytes / 4; }
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
    VertexFormat& AddElement(Attribute attrib, uint count)
    {
        return AddElement(VertexElement(attrib, count));
    }
private:
    std::vector<VertexElement> mElems;
    uint mBytes;
};

}
