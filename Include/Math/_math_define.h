#pragma once

#define GENERAL_MATH_OPERATORS(TYPE) \
    template <typename Type1, typename Type2> TYPE<Type1> operator+(TYPE<Type1> a, const TYPE<Type2>& b) { return a += b; } \
    template <typename Type1, typename Type2> TYPE<Type1> operator-(TYPE<Type1> a, const TYPE<Type2>& b) { return a -= b; } \
    template <typename Type1, typename Type2> TYPE<Type1> operator*(TYPE<Type1> a, const TYPE<Type2>& b) { return a *= b; } \
    template <typename Type1, typename Type2> TYPE<Type1> operator/(TYPE<Type1> a, const TYPE<Type2>& b) { return a /= b; } \
    template <typename Type1, typename Type2> TYPE<Type1> operator+(TYPE<Type1> a, const Type2& b) { return a + TYPE<Type1>(b); } \
    template <typename Type1, typename Type2> TYPE<Type1> operator-(TYPE<Type1> a, const Type2& b) { return a - TYPE<Type1>(b); } \
    template <typename Type1, typename Type2> TYPE<Type1> operator*(TYPE<Type1> a, const Type2& b) { return a * TYPE<Type1>(b); } \
    template <typename Type1, typename Type2> TYPE<Type1> operator/(TYPE<Type1> a, const Type2& b) { return a / TYPE<Type1>(b); } \
    template <typename Type1, typename Type2> TYPE<Type1> operator+(const Type2& a, TYPE<Type1> b) { return TYPE<Type1>(a) + b; } \
    template <typename Type1, typename Type2> TYPE<Type1> operator-(const Type2& a, TYPE<Type1> b) { return TYPE<Type1>(a) - b; } \
    template <typename Type1, typename Type2> TYPE<Type1> operator*(const Type2& a, TYPE<Type1> b) { return TYPE<Type1>(a) * b; } \
    template <typename Type1, typename Type2> TYPE<Type1> operator/(const Type2& a, TYPE<Type1> b) { return TYPE<Type1>(a) / b; }
