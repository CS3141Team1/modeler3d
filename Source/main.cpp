#include <SDL2/Sdl2Backend.h>
#include <SDL2/Sdl2Window.h>
#include <iostream>
#include <cmath>
#include <direct.h>

#include "../Include/Boost.h"
#include "Application.h"
#include "IBackend.h"
#include "Modeler3D.h"
#include "Types.h"

#include "Math/ModelerMath.h"

using namespace Core;
using namespace std;

int main(int argc, char** argv)
{
	cout << "Starting Modeler3D" << endl;

	IBackend* backend = new Sdl2Backend();

	Modeler3D app(backend);
	app.Start();

	delete backend;

	cout << "Exiting Modeler3D" << endl;

	std::string newFold = "C:/Temp/01_Modeler3dTest";
	    	std::string nextFold = "C:/Temp/01_Modeler3dTest/test1";

	    	mkdir(newFold.c_str());
	    	mkdir(nextFold.c_str());

	    	//ListDir(newFold);

	    	vector<string> temp = ListDir(newFold);
	    	if (temp[0] == "test1/") {
	    		cout << "True" << "\n";
	    	}

	return 0;
}
