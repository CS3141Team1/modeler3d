#define DO_UNIT_TESTING 0

#if DO_UNIT_TESTING==1

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch.hpp>
#include <iostream>
#include <cmath>

#include "Types.h"
#include "Math/ModelerMath.h"

//Unit test headers
#include "MathTests.h"

#endif
