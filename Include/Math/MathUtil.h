#pragma once

namespace Core
{

namespace Math
{

template <class T>
T ToRadians(T degrees)
{
    return degrees * 3.14159265358979 / 180.0;
}

template <class T>
T ToDegrees(T radians)
{
    return radians * 180.0 / 3.14159265358979;
}

}

}
