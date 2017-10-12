#pragma once

//Generates all +, -, *, / operator overloads for the passed in type
#define CORE_MATH_GEN_MATH_OPERATORS(TYPE) \
    template <typename Type> TYPE<Type> operator+(TYPE<Type> a, const TYPE<Type>& b) { return a += b; } \
    template <typename Type> TYPE<Type> operator-(TYPE<Type> a, const TYPE<Type>& b) { return a -= b; } \
    template <typename Type> TYPE<Type> operator*(TYPE<Type> a, const TYPE<Type>& b) { return a *= b; } \
    template <typename Type> TYPE<Type> operator/(TYPE<Type> a, const TYPE<Type>& b) { return a /= b; } \
    template <typename Type> TYPE<Type> operator+(TYPE<Type> a, const Type& b) { return a + TYPE<Type>(b); } \
    template <typename Type> TYPE<Type> operator-(TYPE<Type> a, const Type& b) { return a - TYPE<Type>(b); } \
    template <typename Type> TYPE<Type> operator*(TYPE<Type> a, const Type& b) { return a * TYPE<Type>(b); } \
    template <typename Type> TYPE<Type> operator/(TYPE<Type> a, const Type& b) { return a / TYPE<Type>(b); } \
    template <typename Type> TYPE<Type> operator+(const Type& a, TYPE<Type> b) { return TYPE<Type>(a) + b; } \
    template <typename Type> TYPE<Type> operator-(const Type& a, TYPE<Type> b) { return TYPE<Type>(a) - b; } \
    template <typename Type> TYPE<Type> operator*(const Type& a, TYPE<Type> b) { return TYPE<Type>(a) * b; } \
    template <typename Type> TYPE<Type> operator/(const Type& a, TYPE<Type> b) { return TYPE<Type>(a) / b; }
