#include "Modeler3D.h"

#include <iostream>

#include <GL/glew.h>

using namespace std;

namespace Core
{

Modeler3D::Modeler3D(IBackend* backend)
    : Application(backend)
{
}

Modeler3D::~Modeler3D()
{
}

void Modeler3D::OnInit()
{
    cout << "Initializing Modeler3D" << endl;
}

void Modeler3D::OnUpdate(float64 dt)
{
}

void Modeler3D::OnRender()
{
    glClearColor(0.6, 0.8, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Modeler3D::OnDestroy()
{
    cout << "Destroying Modeler3D" << endl;
}

}
