#define DO_UNIT_TESTING    0
#define SHOW_SAMPLE_OUTPUT 1

#if DO_UNIT_TESTING==1

//Catch provides a main that takes precedence
#define CATCH_CONFIG_MAIN

#include <catch.hpp>

//Unit test files
#include "MathTests.h"

#endif
