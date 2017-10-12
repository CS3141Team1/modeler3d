#pragma once

#include <cmath>

#include "Types.h"
#include "_math_define.h"

namespace Core
{

namespace Math
{

/**
 * Struct for a 3-Vector. Contains all operator overloads and math functions.
 *
 * @tparam Type type for the vector values
 */
template <typename Type>
struct Vector3
{
	//Declarations for constant unit vectors and zero vector
	static const Vector3<Type> Up;
	static const Vector3<Type> Down;
	static const Vector3<Type> Left;
	static const Vector3<Type> Right;
	static const Vector3<Type> Forward;
	static const Vector3<Type> Back;
	static const Vector3<Type> Zero;

	//Allowing for different contexts: positional, color, and texture coordinates
	union { Type X, R, S; };
	union { Type Y, G, T; };
	union { Type Z, B, P; };

	//Constructors
	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(Type s) : X(s), Y(s), Z(s) {}
	Vector3(const Type x, const Type y, const Type z) : X(x), Y(y), Z(z) {}
	template <typename Type2, typename Type3, typename Type4> Vector3(const Type2& x, const Type3& y, const Type4& z) : X(x), Y(y), Z(z) {}
	template <typename Type2> Vector3(const Vector3<Type2>& v) : X(v.X), Y(v.Y), Z(v.Z) {}

	//Array access overload
	const Type& operator[](uint i) const { return (&X)[i]; }
	Type& operator[](uint i) { return (&X)[i]; }

    //Assignment overload
    Vector3<Type>& operator=(const Vector3& v)
    {
    	X = v.X;
    	Y = v.Y;
    	Z = v.Z;
    	return *this;
    }

    //Negation overload
    Vector3<Type> operator-() const { return Vector3<Type>(-X, -Y, -Z); }

    //Equality overloads
    bool operator==(const Vector3<Type>& v) { return X == v.X && Y == v.Y && Z == v.Z; }
    bool operator!=(const Vector3<Type>& v) { return !(*this == v); }

    //Math with assignment overloads
    Vector3<Type>& operator+=(const Vector3<Type>& v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
    Vector3<Type>& operator-=(const Vector3<Type>& v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
    Vector3<Type>& operator*=(const Vector3<Type>& v) { X *= v.X; Y *= v.Y; Z *= v.Z; return *this; }
    Vector3<Type>& operator/=(const Vector3<Type>& v) { X /= v.X; Y /= v.Y; Z /= v.Z; return *this; }
};

//Macro to define all standard math for the vector
CORE_MATH_GEN_MATH_OPERATORS(Vector3);

/**
 * Returns the length of a 3-Vector
 *
 * @param v A Vector3<Type>
 * @return Length of the vector of type Type
 */
template <typename Type>
Type Length(const Vector3<Type>& v)
{
    return std::sqrt((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z));
}

/**
 * Returns the length squared of a 3-Vector
 *
 * @param v A Vector3<Type>
 * @return Length squared of the vector of type Type
 */
template <typename Type>
Type LengthSq(const Vector3<Type>& v)
{
    return (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z);
}

/**
 * Returns the dot product of two 3-Vectors
 *
 * @param a A Vector3<Type>
 * @param b A Vector3<Type>
 * @return The dot product of a and b of type Type
 */
template <typename Type>
Type Dot(const Vector3<Type>& a, const Vector3<Type>& b)
{
    return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

/**
 * Returns the cross product of two 3-Vectors
 *
 * @param a A Vector3<Type>
 * @param b A Vector3<Type>
 * @return Vector3<Type> The cross product of a and b
 */
template <typename Type>
Type Cross(const Vector3<Type>& a, const Vector3<Type>& b)
{
    return Vector3<Type>(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X);
}

/**
 * Returns the unit vector of a 3-Vector
 *
 * @param v A Vector3<Type>
 * @return Vector3<Type> The unit vector of v
 */
template <typename Type>
Vector3<Type> Normalize(const Vector3<Type>& v)
{
    Type len = LengthSq(v);

    if (len == 0.0)
    {
        return Vector3<Type>(0);
    }
    else
    {
        return v / std::sqrt(len);
    }
}

//To string
template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector3<Type>& r)
{
    return out << "(" << r.X << ", " << r.Y << ", " << r.Z << ")";
}

//Using right hand rule
//Positive Y is up, negative Y is down
template <typename Type> const Vector3<Type> Vector3<Type>::Up(0, 1, 0);
template <typename Type> const Vector3<Type> Vector3<Type>::Down(0, -1, 0);

//Positive X is right, negative X is left
template <typename Type> const Vector3<Type> Vector3<Type>::Left(-1, 0, 0);
template <typename Type> const Vector3<Type> Vector3<Type>::Right(1, 0, 0);

//Positive Z is "back" aka towards you, Negative Z is "forward" aka into the page
template <typename Type> const Vector3<Type> Vector3<Type>::Forward(0, 0, -1);
template <typename Type> const Vector3<Type> Vector3<Type>::Back(0, 0, 1);

//Zero vector
template <typename Type> const Vector3<Type> Vector3<Type>::Zero(0, 0, 0);

//Type definitions for prettier code and less typing
typedef Vector3<float32> Vector3f;
typedef Vector3<float64> Vector3d;
typedef Vector3<int32> Vector3i;
typedef Vector3<uint32> Vector3ui;
typedef Vector3<int64> Vector3l;
typedef Vector3<uint64> Vector3ul;

}

}
