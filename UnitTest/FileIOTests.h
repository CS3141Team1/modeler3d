#pragma once

#if DO_UNIT_TESTING==1

#include "FileIO.h"
#include <math.h>
#include "Types.h"
#include <vector>
#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

/******************************************
 *
 * Boost Directory Tests
 *
 ******************************************/
    ListDir("C:/");

/******************************************
 *
 * Boost FilIO Tests
 *
 ******************************************/

    boost::filesystem::path obj("Assets/cube.obj");

    FileIO objIn;
    objIn.LoadObj(obj);
    objIn.SaveObj("CubeTest1");




#endif
