#include <iostream>

#include <GL/glew.h>

#include "Application.h"
#include "IEngine.h"
#include "Types.h"

#include "Math/VectorMath.h"

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

	Math::Vector2i test(3);
	Math::Vector2i test2(4);

	Math::Vector2i test3(test + test2);

	std::cout << test3 + 2 << std::endl;
	std::cout << 2 + test3 << std::endl;
	std::cout << test3 + test3 << std::endl;

    return 0;
}
