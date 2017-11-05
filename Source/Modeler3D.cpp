#include "Modeler3D.h"

#include <iostream>

#include <boost/filesystem.hpp>
#include <GL/glew.h>

#include "GUI/AllWidgets.h"
#include "GUI/IAction.h"
#include "Math/VectorMath.h"

#include "FileIO.h"
#include "GuiRenderer.h"

using namespace std;
using namespace Core;
using namespace Core::Math;
using namespace Video;

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

class LoadAction : public Gui::IAction
{
public:
    LoadAction(Modeler3D* modeler, std::string file) : mModeler(modeler), mFile(file) {}
    ~LoadAction() {}

    void OnActionPerformed(Gui::Widget* widget)
    {
        cout << mFile << endl;
    }
private:
    Modeler3D* mModeler;
    std::string mFile;
};

Video::IShader* Shader = nullptr;

float Angle = 0.0f;

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
    : Application(backend),
      mEnv(nullptr),
      mGuiRenderer(nullptr)
{
}

Modeler3D::~Modeler3D()
{
}

void Modeler3D::OnInit()
{
    cout << "Initializing Modeler3D" << endl;

    mEnv = Backend->GetWindow()->GetEnvironment();
    mGuiRenderer = new GuiRenderer(Graphics);
    Shader = Graphics->CreateShader(VertSource, FragSource);

    boost::filesystem::path obj("Assets/pencil.obj");

    FileIO objFile;
    objFile.LoadObj(obj);

    vector<VertexPosition3fNormal3f> vertices;

    std::vector<std::vector<double>> positions;
    std::vector<std::vector<double>> textures;
    std::vector<std::vector<double>> normals;
    std::vector<std::vector<std::vector<int>>> faces;

    objFile.LoadObj2(obj , positions, textures, normals, faces);


    for (uint i = 0; i < faces.size(); i++)
    {
        VertexPosition3fNormal3f verts[3];
        for (uint j = 0; j < 3; j++)
        {
            vector<double> pos = positions[faces[i][j][0] - 1];

            for (uint k = 0; k < 3; k++)
            {

                verts[j].Position[k] = pos[k] * 1.5;
            }

        }
        Vector3f normal = Cross(Normalize( verts[1].Position -  verts[0].Position), Normalize( verts[2].Position -  verts[0].Position));
        verts[0].Normal = normal;
        verts[1].Normal = normal;
        verts[2].Normal = normal;

        vertices.push_back(verts[0]);
        vertices.push_back(verts[1]);
        vertices.push_back(verts[2]);
    }

    Gui::Button* elem1 = new Gui::Button(10,10,80,40,new LoadAction(this, "Assets/bunny.obj"));
    elem1->SetAlignment(0, 1);
    Gui::Button* elem2 = new Gui::Button(10,60,80,40,new LoadAction(this, "Assets/cube.obj"));
    elem2->SetAlignment(0, 1);
    Gui::Button* elem3 = new Gui::Button(10,110,80,40,new LoadAction(this, "Assets/dragon.obj"));
    elem3->SetAlignment(0, 1);
    Gui::Button* elem4 = new Gui::Button(10,160,80,40,new LoadAction(this, "Assets/pencil.obj"));
    elem4->SetAlignment(0, 1);

    mEnv->AddWidget(elem1);
    mEnv->AddWidget(elem2);
    mEnv->AddWidget(elem3);
    mEnv->AddWidget(elem4);

    vbo = Graphics->CreateVertexBuffer(vboFormat, vertices.size(), Video::BufferHint::Static);
    geom = Graphics->CreateGeometry();
    vbo->SetData(reinterpret_cast<float*>(&vertices[0]), 0, vertices.size());
    geom->SetVertexBuffer(vbo);
}

void Modeler3D::OnUpdate(float64 dt)
{
    Angle += 1.0 * dt;

    mEnv->SetSize(Window->GetWidth(), Window->GetHeight());
    mEnv->Update(dt);
}

void Modeler3D::OnRender()
{
    Graphics->SetClearColor(0.3, 0.3, 0.3);
    Graphics->Clear();

    Matrix4f projection = Matrix4f::ToPerspective(Math::ToRadians(70.0f), Graphics->GetAspectRatio(), 0.1f, 1000.0f);
    Matrix4f view = Matrix4f::ToLookAt(Vector3f(0, 1, 2), Vector3f::Zero, Vector3f::Up);
    Matrix4f model = Matrix4f::ToYaw(Angle) * Matrix4f::ToPitch(Angle * 1.3) * Matrix4f::ToRoll(Angle * 1.7) * Matrix4f::ToTranslation(Vector3f(0.2, -0.8, 0));
    Matrix3f normalMat(Inverse(Transpose(model)));

    Shader->SetMatrix4f("Projection", projection);
    Shader->SetMatrix4f("View", view);
    Shader->SetMatrix4f("Model", model);
    Shader->SetMatrix3f("NormalMat", normalMat);

    Graphics->SetShader(Shader);
    Graphics->SetGeometry(geom);
    Graphics->Draw(Video::Primitive::TriangleList, 0, vbo->GetLength());

    mGuiRenderer->Reset();
    mEnv->Draw(mGuiRenderer);
}

void Modeler3D::OnDestroy()
{
    cout << "Destroying Modeler3D" << endl;
    mGuiRenderer->Release();
    Shader->Release();
}

}
