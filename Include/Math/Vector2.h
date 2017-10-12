#pragma once

namespace Core
{

namespace Math
{

template <typename Type>
struct Vector2
{
	static const Vector2<Type> Up;
	static const Vector2<Type> Down;
	static const Vector2<Type> Left;
	static const Vector2<Type> Right;
	static const Vector2<Type> Zero;

    union { Type X, R, S; };
    union { Type Y, G, T; };

    Vector2() : X(0), Y(0) {}
    Vector2(Type s) : X(s), Y(s) {}
    Vector2(const Type x, const Type y) : X(x), Y(y) {}
    template <typename Type2, typename Type3> Vector2(const Type2& x, const Type3& y) : X(x), Y(y) {}
    template <typename Type2> Vector2(const Vector2<Type2>& v) : X(v.X), Y(v.Y) {}

    const Type& operator[](uint i) const { return (&X)[i]; }
    Type& operator[](uint i) { return (&X)[i]; }

    template <typename Type2>
    Vector2<Type>& operator=(const Vector2& v)
    {
    	X = v.X;
    	Y = v.Y;
    	return *this;
    }

    Vector2<Type>& operator-() const { return Vector2<Type>(-X, -Y); }

    template <typename Type2> bool operator==(const Vector2<Type2>& v) { return X == v.X && Y == v.Y; }
    template <typename Type2> bool operator!=(const Vector2<Type2>& v) { return X != v.X || Y != v.Y; }

    template <typename Type2> Vector2<Type2>& operator+=(const Vector2<Type2>& v)  { X += v.X; Y += v.Y; return *this; }
    template <typename Type2> Vector2<Type2>& operator-=(const Vector2<Type2>& v)  { X -= v.X; Y -= v.Y; return *this; }
    template <typename Type2> Vector2<Type2>& operator*=(const Vector2<Type2>& v)  { X *= v.X; Y *= v.Y; return *this; }
    template <typename Type2> Vector2<Type2>& operator/=(const Vector2<Type2>& v)  { X /= v.X; Y /= v.Y; return *this; }
};

template <typename Type> const Vector2<Type> Vector2<Type>::Up(0, 1);
template <typename Type> const Vector2<Type> Vector2<Type>::Down(0, -1);
template <typename Type> const Vector2<Type> Vector2<Type>::Left(-1, 0);
template <typename Type> const Vector2<Type> Vector2<Type>::Right(1, 0);
template <typename Type> const Vector2<Type> Vector2<Type>::Zero(0, 0);

GENERAL_MATH_OPERATORS(Vector2);

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector2<Type>& r)
{
    return out << "(" << r.X << ", " << r.Y << ")";
}

typedef Vector2<float32> Vector2f;
typedef Vector2<float64> Vector2d;
typedef Vector2<int32> Vector2i;
typedef Vector2<uint32> Vector2ui;
typedef Vector2<int64> Vector2l;
typedef Vector2<uint64> Vector2ul;

}

}
