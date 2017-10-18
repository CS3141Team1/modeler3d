#include "Modeler3D.h"

#include <iostream>

#include <GL/glew.h>

using namespace std;

namespace Core
{

Video::VertexFormat vboFormat = Video::VertexFormat()
        .AddElement(Video::Attribute::Position, 3)
        .AddElement(Video::Attribute::Color, 3);
Video::IVertexBuffer* vbo = nullptr;
Video::IGeometry* geom = nullptr;

struct VertexPosition3fColor3f
{

};

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

    vbo = Graphics->CreateVertexBuffer(vboFormat, 3, Video::BufferHint::Static);


    vbo->SetData(vertices, 0, 3);
}

void Modeler3D::OnUpdate(float64 dt)
{
}

void Modeler3D::OnRender()
{
    Graphics->SetClearColor(0.3, 0.3, 0.3);
    Graphics->Clear();

    Graphics->SetGeometry(geom);
    Graphics->Draw(Video::Primitive::TriangleList, 0, 3);
}

void Modeler3D::OnDestroy()
{
    cout << "Destroying Modeler3D" << endl;
}

}
