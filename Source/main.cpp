#include <SDL2/Sdl2Backend.h>
#include <SDL2/Sdl2Window.h>
#include <iostream>
#include <cmath>

#include "../Include/Boost.h"
#include "Application.h"
#include "IBackend.h"
#include "Modeler3D.h"
#include "Types.h"

#include "Math/ModelerMath.h"

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

    //ListDir("C:/");

    return 0;
}
