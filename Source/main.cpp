#include <iostream>

#include "Application.h"
#include "Modeler3D.h"
#include "SDL2/Sdl2Backend.h"

using namespace Core;
using namespace std;

int main(int argc, char** asrgv)
{
    cout << "Starting Modeler3D" << endl;

    IBackend* backend = new Sdl2Backend();

    Modeler3D app(backend);
    app.Start();

    delete backend;

    cout << "Exiting Modeler3D" << endl;

    return 0;
}
