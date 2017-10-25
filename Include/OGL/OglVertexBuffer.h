#pragma once

#include <vector>

#include <GL/glew.h>

#include "IVertexBuffer.h"

namespace Video
{

class OglVertexBuffer : public IVertexBuffer
{
public:
    OglVertexBuffer(VertexFormat format, uint length);
    ~OglVertexBuffer();

    void Release();

    const VertexFormat& GetFormat() const { return mFormat; }

    uint GetLength() const { return mLength; }

    void GetData(float* out, uint start, uint count) const;
    void SetData(float* in, uint start, uint count);

    GLuint GetId() const { return mId; }
private:
    VertexFormat mFormat;
    uint mLength;
    std::vector<uint8> mData;
    GLuint mId;
};

}
