#pragma once

#include "Types.h"

namespace Video
{

enum class Attribute
{
    Position,
    Normal,
    Color,
    Texture0,
    Texture1,
    Texture2,
    Texture3
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

    VertexElement(
            Attribute attrib = Attribute::Position,
            uint count = 3,
            DataType type = DataType::Float32)
        : Attrib(attrib),
          Count(count),
          Type(type) {}
};

class VertexFormat
{
public:
    VertexFormat(VertexElement* elems, uint count)
    {
        mElemCount = count;
        mElems = new VertexElement[count];
        for (uint  i = 0; i < count; i++)
        {
            mElems[i] = elems[i];
        }
    }

    ~VertexFormat()
    {
        delete[] mElems;
    }

    const uint GetElementCount() const { return mElemCount; }
    const VertexElement& GetElement(uint index) const { return mElems[index]; }
    const VertexElement& operator[](uint index) const { return GetElement(index); }
private:
    VertexElement* mElems;
    uint mElemCount;
};

}
