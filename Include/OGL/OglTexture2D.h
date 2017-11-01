#pragma once

#include "ITexture2D.h"

namespace Video
{

class OglTexture2D : public ITexture2D
{
public:
    OglTexture2D(uint width, uint height);
    ~OglTexture2D();


private:

};

}
