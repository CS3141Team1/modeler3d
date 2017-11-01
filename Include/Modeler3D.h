#pragma once

#include "Application.h"
#include "GUI/Environment.h"
#include "Types.h"

namespace Core
{

/**
 * 3D modeler class
 */
class Modeler3D : public Application
{
public:
    Modeler3D(IBackend* backend);
    ~Modeler3D();

    virtual void OnInit();
    virtual void OnUpdate(float64 dt);
    virtual void OnRender();
    virtual void OnDestroy();

private:
    GUInterface::Environment* Env;
};

}
