#include "OGL/OglIndexBuffer.h"

#include <string.h>

namespace Video
{

OglIndexBuffer::OglIndexBuffer(uint length)
    : mLength(length),
      mIndices(length),
      mId(0)
{
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * 4, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

OglIndexBuffer::~OglIndexBuffer()
{
    Release();
}

void OglIndexBuffer::Release()
{
    if (mId != 0)
    {
        glDeleteBuffers(1, &mId);
        mId = 0;
    }
}

void OglIndexBuffer::GetData(uint32* out, uint start, uint count) const
{
    memcpy(out, &mIndices[start], count * 4);
}

void OglIndexBuffer::SetData(const uint32* in, uint start, uint count)
{
    memcpy(&mIndices[start], in, count * 4);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, start * 4, count * 4, &mIndices[start]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
