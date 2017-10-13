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
	//Columns variable
	Math::Vector3<Type> mMatrix[3];

	//Declarations for constant matrices
	static const Matrix3<Type> Identity;
	static const Matrix3<Type> Zero;

	//Constructors
	Matrix3(bool identity = true)
	{
		if(identity) {
			mMatrix[0] = Math::Vector3<Type>(1,0,0);
			mMatrix[1] = Math::Vector3<Type>(0,1,0);
			mMatrix[2] = Math::Vector3<Type>(0,0,1);
		} else {
			mMatrix[0] = Math::Vector3<Type>(0);
			mMatrix[1] = Math::Vector3<Type>(0);
			mMatrix[2] = Math::Vector3<Type>(0);
		}
	}
	Matrix3(const Type& s)
	{
		 mMatrix[0] = Math::Vector3<Type>(s);
		 mMatrix[1] = Math::Vector3<Type>(s);
		 mMatrix[2] = Math::Vector3<Type>(s);
	}
	Matrix3(const Type& x, const Type& y, const Type& z)
	{
		 mMatrix[0] = Math::Vector3<Type>(x);
		 mMatrix[1] = Math::Vector3<Type>(y);
		 mMatrix[2] = Math::Vector3<Type>(z);
	}
	template <typename Type2, typename Type3, typename Type4>
	Matrix3(const Type2& x, const Type3& y, const Type4& z)
	{
		mMatrix[0] = Math::Vector3<Type>(x);
		mMatrix[1] = Math::Vector3<Type>(y);
		mMatrix[2] = Math::Vector3<Type>(z);
	}
	Matrix3(const Math::Vector3<Type>& x, const Math::Vector3<Type>& y, const Math::Vector3<Type>& z)
	{
		mMatrix[0] = x;
		mMatrix[1] = y;
		mMatrix[2] = z;
	}
	template <typename Type2, typename Type3, typename Type4>
	Matrix3(const Math::Vector3<Type2>& x, const Math::Vector3<Type3>& y, const Math::Vector3<Type4>& z)
	{
		mMatrix[0] = x;
		mMatrix[1] = y;
		mMatrix[2] = z;
	}

	//Array access overload
	const Math::Vector3<Type>& operator[](uint i) const { return &mMatrix[i]; }
	Math::Vector3<Type> operator[](uint i) { return mMatrix[i]; }

    //Assignment overload
    Matrix3<Type>& operator=(const Matrix3& v)
    {
    	mMatrix = v.mMatrix;
    	return *this;
    }

    //Negation overload
    Matrix3<Type> operator-() const { return Matrix3<Type>(-mMatrix[0], -mMatrix[1], -mMatrix[2]); }

    //Equality overloads
    bool operator==(const Matrix3<Type>& v) { return mMatrix[0] == v.mMatrix[0] && mMatrix[1] == v.mMatrix[1] && mMatrix[2] == v.mMatrix[2]; }
    bool operator!=(const Matrix3<Type>& v) { return mMatrix[0] != v.mMatrix[0] || mMatrix[1] != v.mMatrix[1] || mMatrix[2] != v.mMatrix[2]; }

    //Math with assignment overloads
    Matrix3<Type>& operator+=(const Matrix3<Type>& v) { mMatrix[0] += v.mMatrix[0]; mMatrix[1] += v.mMatrix[1]; mMatrix[2] += v.mMatrix[2]; return *this; }
    Matrix3<Type>& operator-=(const Matrix3<Type>& v) { mMatrix[0] -= v.mMatrix[0]; mMatrix[1] -= v.mMatrix[1]; mMatrix[2] -= v.mMatrix[2]; return *this; }
    Matrix3<Type>& operator*=(const Matrix3<Type>& v) { mMatrix[0] *= v.mMatrix[0]; mMatrix[1] *= v.mMatrix[1]; mMatrix[2] *= v.mMatrix[2]; return *this; }
    Matrix3<Type>& operator/=(const Matrix3<Type>& v) { mMatrix[0] /= v.mMatrix[0]; mMatrix[1] /= v.mMatrix[1]; mMatrix[2] /= v.mMatrix[2]; return *this; }
};

//Inverse
//Transpose
//Determinant

//To string
template <typename Type>
std::ostream& operator<<(std::ostream& out, const Matrix3<Type>& v)
{
    return out << "[" << v.mMatrix[0][0] << ", " << v.mMatrix[1][0] << ", " << v.mMatrix[2][0] << "]" << std::endl
    		<< "[" << v.mMatrix[0][1] << ", " << v.mMatrix[1][1] << ", " << v.mMatrix[2][1] << "]" << std::endl
			<< "[" << v.mMatrix[0][2] << ", " << v.mMatrix[1][2] << ", " << v.mMatrix[2][2] << "]";
}

template <typename Type>
std::string toString(Matrix3<Type> v) {
	std::string ret = "";
	ret += "[" + v.mMatrix[0][0] + ", " + v.mMatrix[1][0] + ", " + v.mMatrix[2][0] + "]" + std::endl
    		+ "[" + v.mMatrix[0][1] + ", " + v.mMatrix[1][1] + ", " + v.mMatrix[2][1] + "]" + std::endl
			+ "[" + v.mMatrix[0][2] + ", " + v.mMatrix[1][2] + ", " + v.mMatrix[2][2] + "]";
	return ret;
}

//Identity and zero matrices
template <typename Type> const Matrix3<Type> Matrix3<Type>::Identity(true);
template <typename Type> const Matrix3<Type> Matrix3<Type>::Zero(false);

//Type definitions for prettier code and less typing
typedef Matrix3<float32> Matrix3f;
typedef Matrix3<float64> Matrix3d;
typedef Matrix3<int32> Matrix3i;
typedef Matrix3<uint32> Matrix3ui;
typedef Matrix3<int64> Matrix3l;
typedef Matrix3<uint64> Matrix3ul;

}

}
