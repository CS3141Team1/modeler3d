#include "Modeler3D.h"

#include <iostream>

#include <GL/glew.h>

#include "Math/VectorMath.h"

using namespace std;
using namespace Core;
using namespace Core::Math;

//std::string VertSource = ""
//        "#version 120"
//        ""
//        "attribute vec3 aPosition; "
//        "attribute vec3 aNormal; "
//        ""
//        "varying vec3 vPosition; "
//        "varying vec3 vNormal; "
//        ""
//        "uniform mat4 Projection; "
//        "uniform mat4 View; "
//        "uniform mat4 Model; "
//        "uniform mat3 NormalMat; "
//        ""
//        "void main() "
//        "{"
//        "   vNormal = normalize(NormalMat * aNormal); "
//        "   gl_Position = Model * vec4(aPosition); "
//        "   vPosition = gl_Position.xyz / gl_Position.w; "
//        "   gl_Position = Projection * View * gl_Position; "
//        "}";
//
//std::string FragSource = ""
//        "#version 120 "
//        ""
//        "varying vec3 vPosition; "
//        "varying vec3 vNormal; "
//        ""
//        "uniform vec3 LightDirection = vec3(0.0, -1.0, 0.0); "
//        ""
//        "float Diffuse(vec3 normal, vec3 lightDir) "
//        "{"
//        "   return clamp(dot(normal, lightDir), 0.0, 1.0); "
//        "}"
//        ""
//        "void main() "
//        "{"
//        "   vec3 normal = normalize(vNormal); "
//        "   vec3 lightDir = normalize(LightDirection); "
//        ""
//        "   vec3 color = vec3(0.5, 0.5, 0.5); "
//        "   float diffuse = Diffuse(normal, lightDir); "
//        ""
//        "   gl_FragColor = vec4(color * diffuse, 1.0); "
//        "}";

std::string VertSource = ""
        "#version 120 \n"
        ""
        "attribute vec3 aPosition; \n"
        "attribute vec3 aNormal; \n"
        ""
        "varying vec3 vViewPosition; \n"
        "varying vec3 vNormal; \n"
        ""
        "uniform mat4 Projection; \n"
        "uniform mat4 View; \n"
        "uniform mat4 Model; \n"
        "uniform mat3 NormalMat; \n"
        ""
        "void main() \n"
        "{ \n"
        "   vNormal = normalize(NormalMat * aNormal); \n"
        "   gl_Position = View * Model * vec4(aPosition, 1.0); \n"
        "   vViewPosition = gl_Position.xyz / gl_Position.w; \n "
        "   gl_Position = Projection * gl_Position; \n"
        "} \n";

std::string FragSource = ""
        "#version 120 \n"
        ""
        "varying vec3 vViewPosition; \n"
        "varying vec3 vNormal; \n"
        ""
        "uniform vec3 LightDirection = vec3(-1, -0.5, -1); \n"
        ""
        "float Diffuse(vec3 normal, vec3 lightDir) \n"
        "{ \n"
        "   return clamp(dot(normal, -lightDir), 0.0, 1.0); \n"
        "} \n"
        ""
        "float Specular(vec3 normal, vec3 lightDir, vec3 cameraDir, float power) \n"
        "{ \n"
        "   vec3 halfVec = normalize(lightDir + cameraDir); \n"
        "   return pow(clamp(abs(dot(normal, -halfVec)), 0.0, 1.0), power); "
        "} \n"
        ""
        "void main() \n"
        "{ \n"
        "   vec3 normal = normalize(vNormal); \n"
        "   vec3 lightDir = normalize(LightDirection); \n"
        "   vec3 cameraDir = normalize(vViewPosition); \n"
        ""
        "   vec3 color = vec3(1.0); \n"
        "   float diffuse = Diffuse(normal, lightDir); \n"
        "   float specular = Specular(normal, lightDir, cameraDir, 100); \n"
        ""
        "   gl_FragColor = vec4(color * (diffuse * 0.4 + 0.4 + specular * 0.4), 1.0); \n"
        "} \n";

Video::IShader* Shader = nullptr;

namespace Core
{

Video::VertexFormat vboFormat = Video::VertexFormat()
        .AddElement(Video::Attribute::Position, 3)
        .AddElement(Video::Attribute::Normal, 3);
Video::IVertexBuffer* vbo = nullptr;
Video::IGeometry* geom = nullptr;

struct VertexPosition3fNormal3f
{
    Vector3f Position;
    Vector3f Normal;
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

    vbo = Graphics->CreateVertexBuffer(vboFormat, 6 * 6, Video::BufferHint::Static);
    geom = Graphics->CreateGeometry();

    float32 s = 0.5f;

    VertexPosition3fNormal3f vertices[] =
    {
            // front
            { {-s, -s, -s}, {0, 0, -1} },
            { { s, -s, -s}, {0, 0, -1} },
            { { s,  s, -s}, {0, 0, -1} },
            { {-s, -s, -s}, {0, 0, -1} },
            { { s,  s, -s}, {0, 0, -1} },
            { {-s,  s, -s}, {0, 0, -1} },
            // back
            { {-s, -s,  s}, {0, 0, 1} },
            { { s, -s,  s}, {0, 0, 1} },
            { { s,  s,  s}, {0, 0, 1} },
            { {-s, -s,  s}, {0, 0, 1} },
            { { s,  s,  s}, {0, 0, 1} },
            { {-s,  s,  s}, {0, 0, 1} },
            // top
            { {-s,  s, -s}, {0, 1, 0} },
            { { s,  s, -s}, {0, 1, 0} },
            { { s,  s,  s}, {0, 1, 0} },
            { {-s,  s, -s}, {0, 1, 0} },
            { { s,  s,  s}, {0, 1, 0} },
            { {-s,  s,  s}, {0, 1, 0} },
            // bottom
            { {-s, -s, -s}, {0,-1, 0} },
            { { s, -s, -s}, {0,-1, 0} },
            { { s, -s,  s}, {0,-1, 0} },
            { {-s, -s, -s}, {0,-1, 0} },
            { { s, -s,  s}, {0,-1, 0} },
            { {-s, -s,  s}, {0,-1, 0} },
            // right
            { { s, -s, -s}, {1, 0, 0} },
            { { s, -s,  s}, {1, 0, 0} },
            { { s,  s,  s}, {1, 0, 0} },
            { { s, -s, -s}, {1, 0, 0} },
            { { s,  s,  s}, {1, 0, 0} },
            { { s,  s, -s}, {1, 0, 0} },
            // left
            { {-s, -s, -s}, {-1, 0, 0} },
            { {-s, -s,  s}, {-1, 0, 0} },
            { {-s,  s,  s}, {-1, 0, 0} },
            { {-s, -s, -s}, {-1, 0, 0} },
            { {-s,  s,  s}, {-1, 0, 0} },
            { {-s,  s, -s}, {-1, 0, 0} },
    };

    vbo->SetData(vertices, 0, 6 * 6);
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
    Graphics->Draw(Video::Primitive::TriangleList, 0, 2 * 6);
}

void Modeler3D::OnDestroy()
{
    cout << "Destroying Modeler3D" << endl;
}

}
