#pragma once

namespace Video
{

class IIndexBuffer;
class ITexture2D;
class IVertexArray;
class IVertexBuffer;

class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    virtual ITexture2D* CreateTexture(unsigned int width, unsigned int height) = 0;
};

}
