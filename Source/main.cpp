#include <iostream>

#include <GL/glew.h>

#include "Application.h"
#include "IEngine.h"

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

    virtual void OnUpdate(Float64 dt)
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
    IEngine* engine = new Sdl2Engine();
    Modeler3D app(engine);
    engine->Start(&app);

    return 0;
}
