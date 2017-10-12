#pragma once

#include <iostream>
#include <cmath>

#include "Vector3.h"

namespace Core
{

namespace Math
{

/**
 * Matrix3 representation using 3 Vector3 as columns.
 *
 * @tparam Type the type for the values in the matrix
 */
template <typename Type>
struct Matrix3
{
	Math::Vector3<Type> mMatrix[3];

	//Constructors
	Matrix3() : mMatrix[0](0), mMatrix[0](1), mMatrix[2](0) {}
	Matrix3(Type s) : mMatrix[0](s), mMatrix[0](s), mMatrix[2](s) {}
	Matrix3(const Type x, const Type y, const Type z) : mMatrix[0](x), mMatrix[0](y), mMatrix[2](z) {}
};

}

}
