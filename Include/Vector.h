#pragma once

#include "Types.h"

namespace Core
{

namespace Math
{

template <typename Type>
class Vector2
{
    union { Type X, R, S; };
    union { Type Y, G, T; };

    const Type& operator[](uint i) const { return (&X)[i]; }
    Type& operator[](uint i) { return (&X)[i]; }
};

typedef Vector2<float32> Vector2f;
typedef Vector2<float64> Vector2d;
typedef Vector2<int32> Vector2i;
typedef Vector2<uint32> Vector2ui;
typedef Vector2<int64> Vector2l;
typedef Vector2<uint64> Vector2ul;

}

}
