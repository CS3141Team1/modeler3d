#define DO_UNIT_TESTING    1

#define SHOW_SAMPLE_OUTPUT 0

#if DO_UNIT_TESTING==1

#define UNIT_TEST_OUTPUT(command) \
	if (SHOW_SAMPLE_OUTPUT) { \
		command; \
	}

//Catch provides a main that takes precedence
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

//Unit test files
#include "MathTests.h"
#include "FileIOTests.h"

#endif
