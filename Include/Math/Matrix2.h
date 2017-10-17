#pragma once

#include <iostream>
#include <cmath>

#include "Types.h"
#include "Vector2.h"

namespace Core
{

namespace Math
{

/**
 * Matrix2 representation using 2 Vector2 as columns.
 *
 * @author Michael Conard
 * @tparam Type the type for the values in the matrix
 */
template <typename Type>
struct Matrix2
{
	//Columns variable
	Math::Vector2<Type> mMatrix[2];

	//Declarations for constant matrices
	static const Matrix2<Type> Identity;
	static const Matrix2<Type> Zero;

	//Constructors
	Matrix2()
	{
		mMatrix[0] = Math::Vector2<Type>(1,0);
		mMatrix[1] = Math::Vector2<Type>(0,1);
	}
	Matrix2(const Type& s)
	{
		 mMatrix[0] = Math::Vector2<Type>(s);
		 mMatrix[1] = Math::Vector2<Type>(s);
	}
	Matrix2(const Type& x, const Type& y)
	{
		 mMatrix[0] = Math::Vector2<Type>(x);
		 mMatrix[1] = Math::Vector2<Type>(y);
	}
	template <typename Type2, typename Type3>
	Matrix2(const Type2& x, const Type3& y)
	{
		mMatrix[0] = Math::Vector2<Type>(x);
		mMatrix[1] = Math::Vector2<Type>(y);
	}
	Matrix2(const Math::Vector2<Type>& x, const Math::Vector2<Type>& y)
	{
		mMatrix[0] = x;
		mMatrix[1] = y;
	}
	template <typename Type2, typename Type3>
	Matrix2(const Math::Vector2<Type2>& x, const Math::Vector2<Type3>& y)
	{
		mMatrix[0] = x;
		mMatrix[1] = y;
	}

	//Array access overload
	const Math::Vector2<Type>& operator[](uint i) const { return mMatrix[i]; }
	Math::Vector2<Type>& operator[](uint i) { return mMatrix[i]; }

    //Assignment overload
    Matrix2<Type>& operator=(const Matrix2& v)
    {
    	for(int32 i = 0; i < 2; ++i)
    	{
    		mMatrix[i] = v.mMatrix[i];
    	}
    	return *this;
    }

    //Negation overload
    Matrix2<Type> operator-() const { return Matrix2<Type>(-mMatrix[0], -mMatrix[1]); }

    //Equality overloads
    bool operator==(const Matrix2<Type>& v) { return mMatrix[0] == v.mMatrix[0] && mMatrix[1] == v.mMatrix[1]; }
    bool operator!=(const Matrix2<Type>& v) { return mMatrix[0] != v.mMatrix[0] || mMatrix[1] != v.mMatrix[1]; }

    //Math with assignment overloads
    Matrix2<Type>& operator+=(const Matrix2<Type>& v) { mMatrix[0] += v.mMatrix[0]; mMatrix[1] += v.mMatrix[1]; return *this; }
    Matrix2<Type>& operator-=(const Matrix2<Type>& v) { mMatrix[0] -= v.mMatrix[0]; mMatrix[1] -= v.mMatrix[1]; return *this; }
    Matrix2<Type>& operator*=(const Matrix2<Type>& m)
    {
    	Matrix2<Type> copy = *this;
    	for(int32 i = 0; i < 2; ++i)
    	{
    		for(int32 j = 0; j < 2; ++j)
    		{
    			copy.mMatrix[i][j] = mMatrix[0][j] * m.mMatrix[i][0] + mMatrix[1][j] * m.mMatrix[i][1];
    		}
    	}
    	*this = copy;
    	return *this;
    }
    Matrix2<Type>& operator*=(const Type& s)
    {
    	for(int32 i = 0; i < 2; ++i)
    	{
    		for(int32 j = 0; j < 2; ++j)
    		{
    			mMatrix[i][j] *= s;
    		}
    	}
    	return *this;
    }
    Matrix2<Type>& operator/=(Matrix2<Type> m)
    {
    	Matrix2<Type> inv = Inverse(m);
    	(*this) *= inv;
    	return *this;
    }
    Matrix2<Type>& operator/=(const Type& s)
    {
    	for(int32 i = 0; i < 2; ++i)
    	{
    		for(int32 j = 0; j < 2; ++j)
    		{
    			mMatrix[i][j] /= s;
    		}
    	}
    	return *this;
    }
};

//Macro to define all standard math for the matrix
CORE_MATH_GEN_MATRIX_OPERATORS(Matrix2);

//Multiplying with vector
template <typename Type, typename Type2>
Vector2<Type> operator*(const Matrix2<Type>& m, const Vector2<Type2>& v)
{
	Math::Vector2<Type> ret(0);
	for(int32 i = 0; i < 2; ++i)
	{
		Type sum = 0;
		for(int32 j = 0; j < 2; ++j)
		{
			sum += m[j][i] * v[j];
		}
		ret[i] = sum;
	}
	return ret;
}

/**
 * Returns the inverse of a 2x2 Matrix
 *
 * @param m A Matrix2<Type>
 * @return Matrix2<Type> The inverse matrix
 */
template <typename Type>
Matrix2<Type> Inverse(Matrix2<Type> m)
{
	Type a = m[0][0];
	Type b = m[1][0];
	Type c = m[0][1];
	Type d = m[1][1];

	m[0][0] = d;
	m[1][0] = -b;
	m[0][1] = -c;
	m[1][1] = a;

	m /= Determinant(m);

	return m;
}

/**
 * Returns the transpose of a 2x2 Matrix
 *
 * @param m A Matrix2<Type>
 * @return Matrix2<Type> The transposed matrix
 */
template <typename Type>
Matrix2<Type> Transpose(Matrix2<Type>& m)
{
	Matrix2<Type> transpose = m;
	transpose[1][0] = m[0][1];
	transpose[0][1] = m[1][0];
	return transpose;
}

/**
 * Returns the determinant of a 2x2 Matrix
 *
 * @param m A Matrix2<Type>
 * @return Type The determinant of m
 */
template <typename Type>
Type Determinant(Matrix2<Type>& m)
{
	Type a = m[0][0];
	Type b = m[1][0];
	Type c = m[0][1];
	Type d = m[1][1];
	Type det = a*d - b*c;
	return det;
}

//To string
template <typename Type>
std::ostream& operator<<(std::ostream& out, const Matrix2<Type>& m)
{
    return out << "[" << m.mMatrix[0][0] << ", " << m.mMatrix[1][0] << "]" << std::endl
    		<< "[" << m.mMatrix[0][1] << ", " << m.mMatrix[1][1] << "]";
}

template <typename Type>
std::string toString(Matrix2<Type> m) {
	std::string ret = "";
	ret += "[" + m.mMatrix[0][0] + ", " + m.mMatrix[1][0] + "]" + std::endl
    		+ "[" + m.mMatrix[0][1] + ", " + m.mMatrix[1][1] + "]";
	return ret;
}

//Identity and zero matrices
template <typename Type> const Matrix2<Type> Matrix2<Type>::Identity;
template <typename Type> const Matrix2<Type> Matrix2<Type>::Zero(0);

//Type definitions for prettier code and less typing
typedef Matrix2<float32> Matrix2f;
typedef Matrix2<float64> Matrix2d;
typedef Matrix2<int32> Matrix2i;
typedef Matrix2<uint32> Matrix2ui;
typedef Matrix2<int64> Matrix2l;
typedef Matrix2<uint64> Matrix2ul;

}

}
