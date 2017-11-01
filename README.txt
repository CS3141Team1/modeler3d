How To Use Modeler3d

Pre-requisites:

MUST HAVE Boost libraries compiled and linked.
MUST HAVE SDL2 compiled and linked.
MUST HAVE GLEW compiled and linked.

Primary support is for MinGW but it may work on Cygwin or VisualC++.

Right now, it is not usable for a typical person because there is no interface yet. You can follow these steps to display your .obj model.

1. Place a .obj model file in the "Assets" folder

2. In Modeler3d.cpp, in the init method change the file path to be your .obj.

3. Compile and run.
