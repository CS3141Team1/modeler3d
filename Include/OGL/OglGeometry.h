#pragma once

#include "IGeometry.h"

#include "OGL/OglVertexBuffer.h"

#include <vector>

namespace Video
{

class OglGeometry : public IGeometry
{
public:
    OglGeometry() {}
    ~OglGeometry() { Release(); }

    void Release() { mVboList.clear(); }

    uint GetVertexBufferCount() const { return mVboList.size(); }
    const IVertexBuffer* GetVertexBuffer(uint index) const { return mVboList[index]; }
    IVertexBuffer* GetVertexBuffer(uint index) { return mVboList[index]; }

    void SetVertexBuffers(IVertexBuffer** vbos, uint count)
    {
        mVboList.clear();
        for (uint i = 0; i < count; i++)
        {
            OglVertexBuffer* vbo = dynamic_cast<OglVertexBuffer*>(vbos[i]);
            if (vbo)
            {
                mVboList.push_back(vbo);
            }
        }
    }
    void SetVertexBuffer(IVertexBuffer* vbo)
    {
        SetVertexBuffers(&vbo, 1);
    }
private:
    std::vector<OglVertexBuffer*> mVboList;
};

}
