#pragma once

#include <vector>

#include "Math/ModelerMath.h"

#include "IGraphicsDevice.h"
#include "VertexFormat.h"

namespace Video
{

/**
 * Vertex for a mesh
 *
 * @author Nicholas Hamilton
 */
struct MeshVertex
{
    Core::Math::Vector3f Position;
    Core::Math::Vector3f Normal;
};

/**
 * Holds mesh data
 *
 * TODO finish
 *
 * @author Nicholas Hamilton
 */
class Mesh
{
public:
    Mesh(IGraphicsDevice* mGraphics);
    ~Mesh();

    /**
     * Get pointer to position data
     */
    Core::Math::Vector3f* GetPositions() { return &mPositions[0]; }

    /**
     * Get pointer to position data
     */
    const Core::Math::Vector3f* GetPositions() const { return &mPositions[0]; }

    /**
     * Get pointer to normal data
     */
    Core::Math::Vector3f* GetNormals() { return &mNormals[0]; }

    /**
     * Get pointer to normal data
     */
    const Core::Math::Vector3f* GetNormals() const { return &mNormals[0]; }


private:
    std::vector<Core::Math::Vector3f> mPositions;
    std::vector<Core::Math::Vector3f> mNormals;
    IGraphicsDevice* mGraphics;
    IVertexBuffer* mVbo;
    IGeometry* mGeom;
};

}
