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
 * Struct for a 2-Vector. Contains all operator overloads and math functions.
 *
 * @tparam Type type for the vector values
 */
template <typename Type>
struct Vector2
{
	//Declarations for constant unit vectors and zero vector
	static const Vector2<Type> Up;
	static const Vector2<Type> Down;
	static const Vector2<Type> Left;
	static const Vector2<Type> Right;
	static const Vector2<Type> Zero;

	//Allowing for different contexts: positional, color, and texture coordinates
    union { Type X, R, S; };
    union { Type Y, G, T; };

    //Constructors
    Vector2() : X(0), Y(0) {}
    Vector2(Type s) : X(s), Y(s) {}
    Vector2(const Type x, const Type y) : X(x), Y(y) {}
    template <typename Type2, typename Type3> Vector2(const Type2& x, const Type3& y) : X(x), Y(y) {}
    template <typename Type2> Vector2(const Vector2<Type2>& v) : X(v.X), Y(v.Y) {}

    //Array access overload
    const Type& operator[](uint i) const { return (&X)[i]; }
    Type& operator[](uint i) { return (&X)[i]; }

    //Assignment overload
    Vector2<Type>& operator=(const Vector2<Type>& v)
    {
    	X = v.X;
    	Y = v.Y;
    	return *this;
    }

    //Negation overload
    Vector2<Type> operator-() const { return Vector2<Type>(-X, -Y); }

    //Equality overloads
    bool operator==(const Vector2<Type>& v) { return X == v.X && Y == v.Y; }
    bool operator!=(const Vector2<Type>& v) { return !(*this == v); }

    //Math with assignment overloads
    Vector2<Type>& operator+=(const Vector2<Type>& v) { X += v.X; Y += v.Y; return *this; }
    Vector2<Type>& operator-=(const Vector2<Type>& v) { X -= v.X; Y -= v.Y; return *this; }
    Vector2<Type>& operator*=(const Vector2<Type>& v) { X *= v.X; Y *= v.Y; return *this; }
    Vector2<Type>& operator/=(const Vector2<Type>& v) { X /= v.X; Y /= v.Y; return *this; }
};

//Macro to define all standard math for the vector
CORE_MATH_GEN_MATH_OPERATORS(Vector2);

/**
 * Returns the length of a 2-Vector
 *
 * @param v A Vector2<Type>
 * @return Length of the vector of type Type
 */
template <typename Type>
Type Length(const Vector2<Type>& v)
{
    return std::sqrt((v.X * v.X) + (v.Y * v.Y));
}

/**
 * Returns the length squared of a 2-Vector
 *
 * @param v A Vector2<Type>
 * @return Length squared of the vector of type Type
 */
template <typename Type>
Type LengthSq(const Vector2<Type>& v)
{
    return (v.X * v.X) + (v.Y * v.Y);
}

/**
 * Returns the dot product of two 2-Vectors
 *
 * @param a A Vector2<Type>
 * @param b A Vector2<Type>
 * @return The dot product of a and b of type Type
 */
template <typename Type>
Type Dot(const Vector2<Type>& a, const Vector2<Type>& b)
{
    return (a.X * b.X) + (a.Y * b.Y);
}

/**
 * Returns the cross product of two 2-Vectors
 *
 * @param a A Vector2<Type>
 * @param b A Vector2<Type>
 * @return The cross product of a and b of type Type which is the lone Z component
 */
template <typename Type>
Type Cross(const Vector2<Type>& a, const Vector2<Type>& b)
{
    return (a.X * b.Y) - (a.Y * b.X);
}

/**
 * Returns the cross product of a 2-Vector and scalar
 *
 * @param v A Vector2<Type>
 * @param s A scalar of type Type
 * @return Vector2<Type> The cross product of v and s
 */
template <typename Type>
Vector2<Type> Cross(const Vector2<Type>& v, const Type& s)
{
    return Vector2<Type>(v.Y * s, -v.X * s);
}

/**
 * Returns the cross product of a 2-Vector and scalar
 *
 * @param s A scalar of type Type
 * @param a A Vector2<Type>
 * @return Vector2<Type> The cross product of s and v
 */
template <typename Type>
Vector2<Type> Cross(const Type& s, const Vector2<Type>& v)
{
    return Vector2<Type>(-v.Y * s, v.X * s);
}

/**
 * Returns the unit vector of a 2-Vector
 *
 * @param v A Vector2<Type>
 * @return Vector2<Type> The unit vector of v
 */
template <typename Type>
Vector2<Type> Normalize(const Vector2<Type>& v)
{
    Type len = LengthSq(v);

    if (len == 0.0)
    {
        return Vector2<Type>(0);
    }
    else
    {
        return v / std::sqrt(len);
    }
}

//To string
template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector2<Type>& v)
{
    return out << "(" << v.X << ", " << v.Y << ")";
}

template <typename Type>
std::string toString(Vector2<Type> v) {
	std::string ret = "";
	ret += "(" + std::to_string(v.X) + ", " + std::to_string(v.Y) + ")";
	return ret;
}

//Right hand rule
//Positive Y is up, negative Y is down
template <typename Type> const Vector2<Type> Vector2<Type>::Up(0, 1);
template <typename Type> const Vector2<Type> Vector2<Type>::Down(0, -1);

//Positive X is right, negative X is left
template <typename Type> const Vector2<Type> Vector2<Type>::Left(-1, 0);
template <typename Type> const Vector2<Type> Vector2<Type>::Right(1, 0);

//Zero vector
template <typename Type> const Vector2<Type> Vector2<Type>::Zero(0, 0);

//Type definitions for prettier code and less typing
typedef Vector2<float32> Vector2f;
typedef Vector2<float64> Vector2d;
typedef Vector2<int32> Vector2i;
typedef Vector2<uint32> Vector2ui;
typedef Vector2<int64> Vector2l;
typedef Vector2<uint64> Vector2ul;

}

}
