#pragma once

#include "Application.h"
#include "Types.h"

namespace Core
{

class Modeler3D : public Application
{
public:
    Modeler3D(IBackend* backend);
    ~Modeler3D();

    virtual void OnInit();
    virtual void OnUpdate(float64 dt);
    virtual void OnRender();
    virtual void OnDestroy();
};

}
