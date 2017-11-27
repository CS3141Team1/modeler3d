#pragma once

#include <vector>

#include "Math/ModelerMath.h"

#include "IGraphicsDevice.h"
#include "VertexFormat.h"

namespace Video
{

struct MeshVertex
{
    Core::Math::Vector3f Position;
    Core::Math::Vector3f Normal;
};

class Mesh
{
public:
    Mesh(IGraphicsDevice* mGraphics);
    ~Mesh();

    Core::Math::Vector3f* GetPositions() { return &mPositions[0]; }
    const Core::Math::Vector3f* GetPositions() const { return &mPositions[0]; }

    Core::Math::Vector3f* GetNormals() { return &mNormals[0]; }
    const Core::Math::Vector3f* GetNormals() const { return &mNormals[0]; }


private:
    std::vector<Core::Math::Vector3f> mPositions;
    std::vector<Core::Math::Vector3f> mNormals;
    IGraphicsDevice* mGraphics;
    IVertexBuffer* mVbo;
    IGeometry* mGeom;
};

}
