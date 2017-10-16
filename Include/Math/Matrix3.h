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
	Matrix3()
	{
		mMatrix[0] = Math::Vector3<Type>(1,0,0);
		mMatrix[1] = Math::Vector3<Type>(0,1,0);
		mMatrix[2] = Math::Vector3<Type>(0,0,1);
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
	const Math::Vector3<Type>& operator[](uint i) const { return mMatrix[i]; }
	Math::Vector3<Type>& operator[](uint i) { return mMatrix[i]; }

    //Assignment overload
    Matrix3<Type>& operator=(const Matrix3& v)
    {
    	for(int32 i = 0; i < 3; ++i)
    	{
    		mMatrix[i] = v.mMatrix[i];
    	}
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
    Matrix3<Type>& operator*=(const Matrix3<Type>& m)
    {
    	Matrix3<Type> copy = *this;
    	for(int32 i = 0; i < 3; ++i)
    	{
    		for(int32 j = 0; j < 3; ++j)
    		{
    			copy.mMatrix[i][j] = mMatrix[0][j] * m.mMatrix[i][0] + mMatrix[1][j] * m.mMatrix[i][1] + mMatrix[2][j] * m.mMatrix[i][2];
    		}
    	}
    	*this = copy;
    	return *this;
    }
    Matrix3<Type>& operator*=(const Type& s)
    {
    	for(int32 i = 0; i < 3; ++i)
    	{
    		for(int32 j = 0; j < 3; ++j)
    		{
    			mMatrix[i][j] *= s;
    		}
    	}
    	return *this;
    }
    Matrix3<Type>& operator/=(Matrix3<Type> m)
    {
    	Matrix3<Type> inv = Inverse(m);
    	(*this) *= inv;
    	return *this;
    }
    Matrix3<Type>& operator/=(const Type& s)
    {
    	for(int32 i = 0; i < 3; ++i)
    	{
    		for(int32 j = 0; j < 3; ++j)
    		{
    			mMatrix[i][j] /= s;
    		}
    	}
    	return *this;
    }
};

//Macro to define all standard math for the matrix
CORE_MATH_GEN_MATRIX_OPERATORS(Matrix3);

//Multiplying with vector
template <typename Type, typename Type2>
Vector3<Type> operator*(const Matrix3<Type>& m, const Vector3<Type2>& v)
{
	Math::Vector3<Type> ret(0);
	for(int32 i = 0; i < 3; ++i)
	{
		Type sum = 0;
		for(int32 j = 0; j < 3; ++j)
		{
			sum += m[j][i] * v[j];
		}
		ret[i] = sum;
	}
	return ret;
}

//Inverse
template <typename Type>
Matrix3<Type> Inverse(Matrix3<Type> m)
{
	Type determinant = Determinant(m);
	if(determinant == 0)
	{
		Matrix3<Type> ret(0); //return zero matrix
		return ret;
	}
	Matrix3<Type> inverse(0); // inverse of matrix m
	//matrix of cofactors, transposed
	inverse[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
	inverse[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]);
	inverse[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
	inverse[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]);
	inverse[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]);
	inverse[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]);
	inverse[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
	inverse[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]);
	inverse[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]);

	//multiply by inverse determinant
	inverse /= determinant;
	return inverse;
}

//Transpose
template <typename Type>
Matrix3<Type> Transpose(Matrix3<Type>& m)
{
	Matrix3<Type> transpose(0);
	for(int32 i = 0; i < 3; ++i)
	{
		for(int32 j = 0; j < 3; ++j)
		{
			transpose.mMatrix[i][j] = m.mMatrix[j][i];
		}
	}
	return transpose;
}
//Determinant
template <typename Type>
Type Determinant(Matrix3<Type>& m)
{
	Type a = m[0][0];
	Type b = m[1][0];
	Type c = m[2][0];
	Type d = m[0][1];
	Type e = m[1][1];
	Type f = m[2][1];
	Type g = m[0][2];
	Type h = m[1][2];
	Type i = m[2][2];
	Type det = a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
	return det;
}

//To string
template <typename Type>
std::ostream& operator<<(std::ostream& out, const Matrix3<Type>& m)
{
    return out << "[" << m.mMatrix[0][0] << ", " << m.mMatrix[1][0] << ", " << m.mMatrix[2][0] << "]" << std::endl
    		<< "[" << m.mMatrix[0][1] << ", " << m.mMatrix[1][1] << ", " << m.mMatrix[2][1] << "]" << std::endl
			<< "[" << m.mMatrix[0][2] << ", " << m.mMatrix[1][2] << ", " << m.mMatrix[2][2] << "]";
}

template <typename Type>
std::string toString(Matrix3<Type> m) {
	std::string ret = "";
	ret += "[" + m.mMatrix[0][0] + ", " + m.mMatrix[1][0] + ", " + m.mMatrix[2][0] + "]" + std::endl
    		+ "[" + m.mMatrix[0][1] + ", " + m.mMatrix[1][1] + ", " + m.mMatrix[2][1] + "]" + std::endl
			+ "[" + m.mMatrix[0][2] + ", " + m.mMatrix[1][2] + ", " + m.mMatrix[2][2] + "]";
	return ret;
}

//Identity and zero matrices
template <typename Type> const Matrix3<Type> Matrix3<Type>::Identity(Math::Vector3<Type>(1,0,0),Math::Vector3<Type>(0,1,0),Math::Vector3<Type>(0,0,1));
template <typename Type> const Matrix3<Type> Matrix3<Type>::Zero(0);

//Type definitions for prettier code and less typing
typedef Matrix3<float32> Matrix3f;
typedef Matrix3<float64> Matrix3d;
typedef Matrix3<int32> Matrix3i;
typedef Matrix3<uint32> Matrix3ui;
typedef Matrix3<int64> Matrix3l;
typedef Matrix3<uint64> Matrix3ul;

}

}
