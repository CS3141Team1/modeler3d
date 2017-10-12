#pragma once

namespace Core
{

namespace Math
{

template <typename Type>
struct Vector4
{
	union { Type X, R, S; };
	union { Type Y, G, T; };
	union { Type Z, B, P; };
	union { Type W, A, Q; };

	const Type& operator[](uint i) const { return (&X)[i]; }
	Type& operator[](uint i) { return (&X)[i]; }
};

GENERAL_MATH_OPERATORS(Vector4);

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector4<Type>& r)
{
    return out << "(" << r.X << ", " << r.Y << ", " << r.Z << ", " << r.W << ")";
}

typedef Vector4<float32> Vector4f;
typedef Vector4<float64> Vector4d;
typedef Vector4<int32> Vector4i;
typedef Vector4<uint32> Vector4ui;
typedef Vector4<int64> Vector4l;
typedef Vector4<uint64> Vector4ul;

}

}
