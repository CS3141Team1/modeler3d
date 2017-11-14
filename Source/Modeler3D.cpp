#include "Modeler3D.h"

#include <cmath>
#include <iostream>

#include <boost/filesystem.hpp>
#include <GL/glew.h>

#include "GUI/AllWidgets.h"
#include "GUI/IAction.h"
#include "Math/ModelerMath.h"

#include "FileIO.h"
#include "GuiRenderer.h"
#include "ModelerActions.h"

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
        "   vViewPosition = gl_Position.xyz; \n "
        "   gl_Position = Projection * gl_Position; \n"
        "} \n";

std::string FragSource = ""
        "#version 120 \n"
        ""
        "varying vec3 vViewPosition; \n"
        "varying vec3 vNormal; \n"
        ""
        "uniform vec3 LightDirection = vec3(-1, -0.5, -1); \n"
        "uniform mat4 View; \n"
        ""
        "float Diffuse(vec3 normal, vec3 lightDir) \n"
        "{ \n"
        "   return clamp((dot(normal, -lightDir)), 0.0, 1.0); \n"
        "} \n"
        ""
        "float Specular(vec3 normal, vec3 lightDir, vec3 cameraDir, float power) \n"
        "{ \n"
        "   vec3 halfVec = normalize(lightDir + cameraDir); \n"
        "   return pow(clamp(dot(normal, -halfVec), 0.0, 1.0), power); "
        "} \n"
        ""
        "void main() \n"
        "{ \n"
        "   vec3 normal = normalize((View * vec4(vNormal, 0.0)).xyz); \n"
        "   vec3 lightDir = normalize((View * vec4(LightDirection, 1.0)).xyz); \n"
        "   vec3 cameraDir = normalize(vViewPosition); \n"
        ""
        "   vec3 color = vec3(0.8, 0.6, 0.4); \n"
        "   float diffuse = Diffuse(normal, lightDir); \n"
        "   float specular = Specular(normal, lightDir, cameraDir, 100); \n"
        ""
        "   gl_FragColor = vec4(color * (diffuse * 0.4 + 0.4 + specular * 0.4), 1.0); \n"
        "} \n";

Video::IShader* Shader = nullptr;

float Angle = 0.0f;

namespace Core
{

Video::VertexFormat vboFormat = Video::VertexFormat()
        .AddElement(Video::Attribute::Position, 3)
        .AddElement(Video::Attribute::Normal, 3);

struct VertexPosition3Normal3
{
    Vector3f Position;
    Vector3f Normal;
};

Modeler3D::Modeler3D(IBackend* backend)
    : Application(backend),
      mEnv(nullptr),
      mGuiRenderer(nullptr),
      mShader(nullptr),
      mGeometry(nullptr),
      mVbo(nullptr),
      mAngle(0),
	  mMouse(backend->GetWindow()->GetMouse()),
	  mZoom(2)
{
	mCamera = new Camera(backend->GetWindow()->GetWidth(),backend->GetWindow()->GetHeight(), Math::Vector3f(0,0,1), Math::Quaternionf());
}

Modeler3D::~Modeler3D() {}

void Modeler3D::LoadObj(const string& file)
{
	boost::filesystem::path obj(file);

	FileIO objFile;

	vector<VertexPosition3Normal3> vertices;
	std::vector<std::vector<double>> positions;
	std::vector<std::vector<double>> textures;
	std::vector<std::vector<double>> normals;
	std::vector<std::vector<std::vector<int>>> faces;

	objFile.LoadObj2(obj , positions, textures, normals, faces);

    for (uint i = 0; i < faces.size(); i++)
    {
        VertexPosition3Normal3 verts[3];
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

    mVbo = Graphics->CreateVertexBuffer(vboFormat, vertices.size(), Video::BufferHint::Static);
    mVbo->SetData((float32*)(&vertices[0]), 0, vertices.size());
    mGeometry->SetVertexBuffer(mVbo);
}

void Modeler3D::OnInit()
{
    cout << "Initializing Modeler3D" << endl;

    mGeometry = Graphics->CreateGeometry();

    mEnv = Backend->GetWindow()->GetEnvironment();
    mGuiRenderer = new GuiRenderer(Graphics);
    mShader = Graphics->CreateShader(VertSource, FragSource);

    Video::ITexture2D* tex = Graphics->CreateTexture2D("Assets/button.png");
    mGuiRenderer->SetTexture(tex);

    Gui::Button* LoadButton1 = new Gui::Button(10, 10 + 58 * 0, 96, 48, new LoadAction(this, "Assets/bunny.obj"), "bunny.obj");
    Gui::Button* LoadButton2 = new Gui::Button(10, 10 + 58 * 1, 96, 48, new LoadAction(this, "Assets/cube.obj"), "cube.obj");
    Gui::Button* LoadButton3 = new Gui::Button(10, 10 + 58 * 2, 96, 48, new LoadAction(this, "Assets/dragon-big.obj"), "dragon.obj");
    Gui::Button* LoadButton4 = new Gui::Button(10, 10 + 58 * 3, 96, 48, new LoadAction(this, "Assets/ferrari.obj"), "ferrari.obj");

    Gui::Widget* ZoomButton1 = new Gui::Button(10, 10 + 58 * 0,96,48, new ZoomAction(this, mCamera, 1), "Zoom 1x");
    Gui::Widget* ZoomButton2 = new Gui::Button(10, 10 + 58 * 1,96,48, new ZoomAction(this, mCamera, 58), "Zoom 58x");
    Gui::Widget* ZoomButton3 = new Gui::Button(10, 10 + 58 * 2,96,48, new ZoomAction(this, mCamera, 300), "Zoom 300x");
    Gui::Widget* ZoomButton4 = new Gui::Button(10, 10 + 58 * 3,96,48, new ZoomAction(this, mCamera, 1000), "Zoom 1000x");

    Gui::Widget* RotatePitchNegButton = new Gui::Button(10 + 106 * 0, 10 + 58 * 0,96,48, new RotateAction(this, mCamera, 1, -1), "Up");
    Gui::Widget* RotatePitchPosButton = new Gui::Button(10 + 106 * 1, 10 + 58 * 0,96,48, new RotateAction(this, mCamera,1, 1), "Down");
    Gui::Widget* RotateYawNegButton = new Gui::Button(10 + 106 * 0, 10 + 58 * 1,96,48, new RotateAction(this, mCamera, 2, -1), "Left");
    Gui::Widget* RotateYawPosButton = new Gui::Button(10 + 106 * 1, 10 + 58 * 1,96,48, new RotateAction(this, mCamera,2, 1), "Right");

    Gui::Screen* Screen = new Gui::Screen(new ScreenMoveAction(this));

    LoadButton1->SetAlignment(0, 1);
    LoadButton2->SetAlignment(0, 1);
    LoadButton3->SetAlignment(0, 1);
    LoadButton4->SetAlignment(0, 1);

    ZoomButton1->SetAlignment(1, 1);
    ZoomButton2->SetAlignment(1, 1);
    ZoomButton3->SetAlignment(1, 1);
    ZoomButton4->SetAlignment(1, 1);

    RotatePitchNegButton->SetAlignment(0, 0);
    RotatePitchPosButton->SetAlignment(0, 0);
    RotateYawNegButton->SetAlignment(0, 0);
    RotateYawPosButton->SetAlignment(0, 0);

    mEnv->AddWidget(LoadButton1);
    mEnv->AddWidget(LoadButton2);
    mEnv->AddWidget(LoadButton3);
    mEnv->AddWidget(LoadButton4);

    mEnv->AddWidget(ZoomButton1);
    mEnv->AddWidget(ZoomButton2);
    mEnv->AddWidget(ZoomButton3);
    mEnv->AddWidget(ZoomButton4);

    mEnv->AddWidget(RotatePitchNegButton);
    mEnv->AddWidget(RotatePitchPosButton);
    mEnv->AddWidget(RotateYawNegButton);
    mEnv->AddWidget(RotateYawPosButton);

    cout << Screen << endl;
    mEnv->AddWidget(Screen);
}

void Modeler3D::OnUpdate(float64 dt)
{
    mAngle += 1.0 * dt;

	int32 amt = mMouse->GetWheelScroll();
	float32 zoom = 1.1;
	if (amt < 0)
	{
	    mZoom *= zoom;
	}
	else if (amt > 0)
	{
	    mZoom /= zoom;
	}

	mCamera->SetPosition(Normalize(mCamera->GetPosition()) * mZoom);

    mEnv->SetSize(Window->GetWidth(), Window->GetHeight());
    mEnv->Update(dt);
}

void Modeler3D::OnRender()
{
    Graphics->SetClearColor(0.3, 0.3, 0.3);
    Graphics->Clear();

    if (mVbo)
    {
    	Camera::Projection proj = mCamera->GetProjectionType();
    	Matrix4f projection;
    	if(proj == Camera::Projection::PERSPECTIVE) projection = mCamera->GetProjection(Math::ToRadians(70.0f), Graphics->GetAspectRatio(), 0.1f, 3000.0f);
    	else projection = mCamera->GetProjection(0.1f, 3000.0f, 0, 0, 0, 0);

        Matrix4f view = mCamera->GetView();

        Matrix4f model = Matrix4f::Identity;
//        Matrix4f model = Matrix4f::ToYaw(mAngle) * Matrix4f::ToPitch(mAngle * 1.3) * Matrix4f::ToRoll(mAngle * 1.7);// * Matrix4f::ToTranslation(Vector3f(0.2, -0.8, 0));

        Matrix3f normalMat(Inverse(Transpose(model)));

        mShader->SetMatrix4f("Projection", projection);
        mShader->SetMatrix4f("View", view);
        mShader->SetMatrix4f("Model", model);
        mShader->SetMatrix3f("NormalMat", normalMat);

        Graphics->SetShader(mShader);
        Graphics->SetGeometry(mGeometry);

        Graphics->Draw(Video::Primitive::TriangleList, 0, mVbo->GetLength() / 3);
    }

    mGuiRenderer->Reset();
    mEnv->Draw(mGuiRenderer);
}

void Modeler3D::SetZoom(float32 zoom) { mZoom = zoom; }

void Modeler3D::OnDestroy()
{
    cout << "Destroying Modeler3D" << endl;
    mGuiRenderer->Release();
    mShader->Release();
    mGeometry->SetVertexBuffer(nullptr);
    mGeometry->Release();
    mVbo->Release();
}

}
