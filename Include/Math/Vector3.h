#pragma once

namespace Core
{

namespace Math
{

template <typename Type>
struct Vector3
{
	union { Type X, R, S; };
	union { Type Y, G, T; };
	union { Type Z, B, P; };

	const Type& operator[](uint i) const { return (&X)[i]; }
	Type& operator[](uint i) { return (&X)[i]; }
};

GENERAL_MATH_OPERATORS(Vector3);

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector3<Type>& r)
{
    return out << "(" << r.X << ", " << r.Y << ", " << r.Z << ")";
}

typedef Vector3<float32> Vector3f;
typedef Vector3<float64> Vector3d;
typedef Vector3<int32> Vector3i;
typedef Vector3<uint32> Vector3ui;
typedef Vector3<int64> Vector3l;
typedef Vector3<uint64> Vector3ul;

}

}
