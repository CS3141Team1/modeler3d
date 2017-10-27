#pragma once

#include <vector>

#include <GL/glew.h>

#include "IIndexBuffer.h"

namespace Video
{

class OglIndexBuffer : public IIndexBuffer
{
public:
    OglIndexBuffer(uint length);
    ~OglIndexBuffer();

    void Release();

    uint GetLength() const { return mLength; }

    void GetData(uint32* out, uint start, uint count) const;
    void SetData(const uint32* in, uint start, uint count);

    GLuint GetId() const { return mId; }
private:
    uint mLength;
    std::vector<uint32> mIndices;
    GLuint mId;
};

}
