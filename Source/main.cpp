#include <iostream>
#include <cmath>

#include <GL/glew.h>

#include "Application.h"
#include "IEngine.h"
#include "Types.h"

#include "Math/VectorMath.h"
#include "Math/MatrixMath.h"

#include "Sdl2/Sdl2Engine.h"

using namespace Core;

class Modeler3D : public Application
{
public:
    Modeler3D(IEngine* engine)
        : Application(engine)
    {
    }

    virtual void OnInit()
    {
        std::cout << "Initializing application" << std::endl;
    }

    virtual void OnUpdate(float64 dt)
    {
    }

    virtual void OnRender()
    {
        glClearColor(0.7, 0.8, 0.9, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    virtual void OnExit()
    {
        std::cout << "Exiting application" << std::endl;
    }
};

int main(int argc, char** asrgv)
{
//    IEngine* engine = new Sdl2Engine();
//    Modeler3D app(engine);
//    engine->Start(&app);

	Math::Vector4f v1(2,1,-3,0);
	Math::Vector4f v2(-1,2,1,1);
	Math::Vector4f v3(0,-4,-2,4);
	Math::Vector4f v4(3,0,5,3);
	Math::Matrix4f test(v1,v2,v3,v4);

	Math::Inverse(test);

    return 0;
}
