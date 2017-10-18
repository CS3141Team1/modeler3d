#include "Modeler3D.h"

#include <iostream>

#include <GL/glew.h>

#include "Math/VectorMath.h"

using namespace std;
using namespace Core;
using namespace Core::Math;

std::string VertSource = ""
        "#version 120"
        ""
        "attribute vec3 aPosition; "
        "attribute vec3 aNormal; "
        ""
        "varying vec3 vPosition; "
        "varying vec3 vNormal; "
        ""
        "uniform mat4 Projection; "
        "uniform mat4 View; "
        "uniform mat4 Model; "
        "uniform mat3 NormalMat; "
        ""
        "void main() "
        "{"
        "   vNormal = normalize(NormalMat * aNormal); "
        "   gl_Position = Model * vec4(aPosition); "
        "   vPosition = gl_Position.xyz / gl_Position.w; "
        "   gl_Position = Projection * View * gl_Position; "
        "}";

std::string FragSource = ""
        "#version 120 "
        ""
        "varying vec3 vPosition; "
        "varying vec3 vNormal; "
        ""
        "uniform vec3 LightDirection = vec3(0.0, -1.0, 0.0); "
        ""
        "float Diffuse(vec3 normal, vec3 lightDir) "
        "{"
        "   return clamp(dot(normal, lightDir), 0.0, 1.0); "
        "}"
        ""
        "void main() "
        "{"
        "   vec3 normal = normalize(vNormal); "
        "   vec3 lightDir = normalize(LightDirection); "
        ""
        "   vec3 color = vec3(0.5, 0.5, 0.5); "
        "   float diffuse = Diffuse(normal, lightDir); "
        ""
        "   gl_FragColor = vec4(color * diffuse, 1.0); "
        "}";

Video::IShader* Shader = nullptr;

namespace Core
{

Video::VertexFormat vboFormat = Video::VertexFormat()
        .AddElement(Video::Attribute::Position, 3)
        .AddElement(Video::Attribute::Color, 3);
Video::IVertexBuffer* vbo = nullptr;
Video::IGeometry* geom = nullptr;

struct VertexPosition3fColor3f
{
    Vector3f Position;
    Vector3f Color;
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

    Shader = Graphics->CreateShader(VertSource, FragSource);

    vbo = Graphics->CreateVertexBuffer(vboFormat, 3, Video::BufferHint::Static);
    geom = Graphics->CreateGeometry();

    VertexPosition3fColor3f vertices[] =
    {
            { Vector3f(-0.5f, -0.5f, 0.0f), Vector3f(1, 0, 0) },
            { Vector3f( 0.5f, -0.5f, 0.0f), Vector3f(0, 1, 0) },
            { Vector3f( 0.0f,  0.5f, 0.0f), Vector3f(0, 0, 1) }
    };

    vbo->SetData(vertices, 0, 3);
    geom->SetVertexBuffer(vbo);
}

void Modeler3D::OnUpdate(float64 dt)
{
}

void Modeler3D::OnRender()
{
    Graphics->SetClearColor(0.3, 0.3, 0.3);
    Graphics->Clear();

    Graphics->SetShader(Shader);
    Graphics->SetGeometry(geom);
    Graphics->Draw(Video::Primitive::TriangleList, 0, 3);
}

void Modeler3D::OnDestroy()
{
    cout << "Destroying Modeler3D" << endl;
}

}
