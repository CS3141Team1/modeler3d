#include "OGL/OglVertexBuffer.h"

#include <string.h>

#include "IVertexBuffer.h"
#include "Types.h"

namespace Video
{

OglVertexBuffer::OglVertexBuffer(VertexFormat format, uint length)
    : mFormat(format),
      mLength(length),
      mData(length * format.GetSizeInBytes()),
      mId(0)
{
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    glBufferData(GL_ARRAY_BUFFER, length * GetSizeInBytes(), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OglVertexBuffer::~OglVertexBuffer()
{
    Release();
}

void OglVertexBuffer::Release()
{
    if (mId != 0)
    {
        glDeleteBuffers(1, &mId);
    }
    mId = 0;
}

void OglVertexBuffer::GetData(float32* out, uint start, uint count) const
{
    uint index = start * mFormat.GetSizeInBytes();
    uint size = count * mFormat.GetSizeInBytes();
    memcpy(out, &mData[index], size);
}

void OglVertexBuffer::SetData(const float32* in, uint start, uint count)
{
    uint index = start * mFormat.GetSizeInBytes();
    uint size = count * mFormat.GetSizeInBytes();

    memcpy(&mData[index], in, size);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    glBufferSubData(GL_ARRAY_BUFFER, index, size, &mData[index]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}
