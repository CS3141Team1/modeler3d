#pragma once

#include <cmath>
#include <iostream>

#include "Types.h"
#include "_math_define.h"

namespace Core
{

namespace Math
{

/**
 * Struct for a 4-Vector. Contains all operator overloads and math functions.
 *
 * @author Michael Conard
 * @tparam Type type for the vector values
 */
template <typename Type>
struct Vector4
{
	//Declarations for constant unit vectors and zero vector
	static const Vector4<Type> E3;
	static const Vector4<Type> Zero;

	//Allowing for different contexts: positional, color, and texture coordinates
	union { Type X, R, S; };
	union { Type Y, G, T; };
	union { Type Z, B, P; };
	union { Type W, A, Q; };

	//Constructors
	Vector4() : X(0), Y(0), Z(0), W(0) {}
	Vector4(const Type& s) : X(s), Y(s), Z(s), W(s) {}
	Vector4(const Type& x, const Type& y, const Type& z, const Type& w) : X(x), Y(y), Z(z), W(w) {}
	template <typename Type2, typename Type3, typename Type4, typename Type5> Vector4(const Type2& x, const Type3& y, const Type4& z, const Type5& w) : X(x), Y(y), Z(z), W(w) {}
	template <typename Type2> Vector4(const Vector4<Type2>& v) : X(v.X), Y(v.Y), Z(v.Z), W(v.W) {}

	//Array access overload
	const Type& operator[](uint i) const { return (&X)[i]; }
	Type& operator[](uint i) { return (&X)[i]; }

    //Assignment overload
    Vector4<Type>& operator=(const Vector4& v)
    {
    	X = v.X;
    	Y = v.Y;
    	Z = v.Z;
    	W = v.W;
    	return *this;
    }

    //Negation overload
    Vector4<Type> operator-() const { return Vector4<Type>(-X, -Y, -Z, -W); }

    //Equality overloads
    bool operator==(const Vector4<Type>& v) { return X == v.X && Y == v.Y && Z == v.Z && W == v.W; }
    bool operator!=(const Vector4<Type>& v) { return !(*this == v); }

    //Math with assignment overloads
    Vector4<Type>& operator+=(const Vector4<Type>& v)  { X += v.X; Y += v.Y; Z += v.Z; W += v.W; return *this; }
    Vector4<Type>& operator-=(const Vector4<Type>& v)  { X -= v.X; Y -= v.Y; Z -= v.Z; W -= v.W; return *this; }
    Vector4<Type>& operator*=(const Vector4<Type>& v)  { X *= v.X; Y *= v.Y; Z *= v.Z; W *= v.W; return *this; }
    Vector4<Type>& operator/=(const Vector4<Type>& v)  { X /= v.X; Y /= v.Y; Z /= v.Z; W /= v.W; return *this; }
};

//Macro to define all standard math for the vector
CORE_MATH_GEN_VECTOR_OPERATORS(Vector4);

/**
 * Returns the length of a 4-Vector
 *
 * @param v A Vector4<Type>
 * @return Length of the vector of type Type
 */
template <typename Type>
Type Length(const Vector4<Type>& v)
{
    return std::sqrt((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z) + (v.W * v.W));
}

/**
 * Returns the length squared of a 4-Vector
 *
 * @param v A Vector4<Type>
 * @return Length squared of the vector of type Type
 */
template <typename Type>
Type LengthSq(const Vector4<Type>& v)
{
    return (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z) + (v.W * v.W);
}

/**
 * Returns the dot product of two 4-Vectors
 *
 * @param a A Vector4<Type>
 * @param b A Vector4<Type>
 * @return The dot product of a and b of type Type
 */
template <typename Type>
Type Dot(const Vector4<Type>& a, const Vector4<Type>& b)
{
    return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z) + (a.W * b.W);
}

/**
 * Returns the unit vector of a 4-Vector
 *
 * @param v A Vector4<Type>
 * @return Vector4<Type> The unit vector of v
 */
template <typename Type>
Vector4<Type> Normalize(const Vector4<Type>& v)
{
    Type len = LengthSq(v);

    if (len == 0.0)
    {
        return Vector4<Type>(0);
    }
    else
    {
        return v / std::sqrt(len);
    }
}

//To string
template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector4<Type>& v)
{
    return out << "(" << v.X << ", " << v.Y << ", " << v.Z << ", " << v.W << ")";
}

template <typename Type>
std::string toString(Vector4<Type> v) {
	std::string ret = "";
	ret += "(" + std::to_string(v.X) + ", " + std::to_string(v.Y) + ", " + std::to_string(v.Z) + ", " + std::to_string(v.W) + ")";
	return ret;
}

//E3, (0,0,0,1)
template <typename Type> const Vector4<Type> Vector4<Type>::E3(0, 0, 0, 1);

//Zero vector
template <typename Type> const Vector4<Type> Vector4<Type>::Zero(0, 0, 0, 0);

//Type definitions for prettier code and less typing
typedef Vector4<float32> Vector4f;
typedef Vector4<float64> Vector4d;
typedef Vector4<int32> Vector4i;
typedef Vector4<uint32> Vector4ui;
typedef Vector4<int64> Vector4l;
typedef Vector4<uint64> Vector4ul;

}

}
