#define DO_UNIT_TESTING 0

#if DO_UNIT_TESTING==1

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch.hpp>
#include <iostream>
#include <cmath>

#include "Types.h"
#include "Math/ModelerMath.h"

//************************* Helpers *************************
template <typename Type>
bool matrixFuzzyEquals(Type a, Type b)
{
	int32 len = sizeof(a)/sizeof(a[0]);
	bool fuzzyEquals = true;
	for(int32 i = 0; i < len; ++i)
	{
		for(int32 j = 0; j < len; ++j)
		{
			if(a[i][j] != Approx(b[i][j])) {
				fuzzyEquals = false;
			}
		}
	}
	return fuzzyEquals;
}

template <typename Type>
bool vectorFuzzyEquals(Type a, Type b)
{
	int32 len = sizeof(a)/sizeof(a[0]);
	bool fuzzyEquals = true;
	for(int32 i = 0; i < len; ++i)
	{
		if(a[i] != Approx(b[i])) {
			fuzzyEquals = false;
		}
	}
	return fuzzyEquals;
}

template <typename Type>
bool quaternionFuzzyEquals(Type a, Type b)
{
	int32 len = 4;
	bool fuzzyEquals = true;
	for(int32 i = 0; i < len; ++i)
	{
		if(a[i] != Approx(b[i])) {
			fuzzyEquals = false;
		}
	}
	return fuzzyEquals;
}

//************************* Vectors *************************
TEST_CASE( "Vector2 methods work correctly with int", "[math][vector][vector-2]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector2i constructor1(2);
	Math::Vector2i constructor2(2,3);
	Math::Vector2i constructor3(constructor1);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );

	SECTION("methods outside of the Vector2 struct using int") {
		CHECK( Math::toString(constructor1) == "(2, 2)" );
		CHECK( Math::toString(constructor2) == "(2, 3)" );

		REQUIRE( Math::Length(constructor1) == 2 ); //real 2.8, should truncate to maintain type
		REQUIRE( Math::LengthSq(constructor1) == 8 );

		CHECK( Math::Dot(constructor1,constructor1) == 8 );
		CHECK( Math::Cross(constructor1,constructor1) == 0 );
		Math::Vector2i testingCrossProdWithConst(4,-4);
		CHECK( Math::Cross(constructor1,2) == testingCrossProdWithConst );
		Math::Vector2i testingCrossProdConstFirst(-4,4);
		CHECK( Math::Cross(2,constructor1) == testingCrossProdConstFirst );
	}

	SECTION("operators inside of the Vector2 struct using int") {
		CHECK( (constructor1[0] == 2 && constructor1[1] == 2) );

		Math::Vector2i testingNegation(-2);
		CHECK( -constructor1 == testingNegation );

		constructor1 = 2;
		Math::Vector2i testingPlusEquals(4,5);
		CHECK( (constructor1 += constructor2) == testingPlusEquals);

		constructor1 = 2;
		Math::Vector2i testingMinusEquals(0,-1);
		CHECK( (constructor1 -= constructor2) == testingMinusEquals);

		constructor1 = 2;
		Math::Vector2i testingTimesEquals(4,6);
		CHECK( (constructor1 *= constructor2) == testingTimesEquals);

		constructor1 = 2;
		Math::Vector2i testingDivideEquals(1,0); //integer division
		CHECK( (constructor1 /= constructor2) == testingDivideEquals);

		constructor1 = 2;
		Math::Vector2i testingPlusEqualsConstant(3,3);
		CHECK( (constructor1 += 1) == testingPlusEqualsConstant );
	}
}

TEST_CASE( "Vector2 methods work correctly with float", "[math][vector][vector-2]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector2f constructor1(2.0);
	Math::Vector2f constructor2(2.0,3.5);
	Math::Vector2f constructor3(constructor1);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );

	SECTION("methods outside of the Vector2 struct using float") {
		CHECK( Math::toString(constructor1) == "(2.000000, 2.000000)" );
		CHECK( Math::toString(constructor2) == "(2.000000, 3.500000)" );

		REQUIRE( Math::Length(constructor1) == Approx(std::sqrt(8)) );
		REQUIRE( Math::LengthSq(constructor1) == Approx(8.0) );

		CHECK( Math::Dot(constructor1,constructor1) == Approx(8.0) );
		CHECK( Math::Dot(constructor1,constructor2) == Approx(11.0) );

		CHECK( Math::Cross(constructor1,constructor1) == Approx(0.0) );
		Math::Vector2f testingCrossProdWithConst(4.0,-4.0);
		CHECK( Math::Cross(constructor1,2.0f) == testingCrossProdWithConst );
		Math::Vector2f testingCrossProdConstFirst(-4.0,4.0);
		CHECK( Math::Cross(2.0f,constructor1) == testingCrossProdConstFirst );

		Math::Vector2f testingNormalize(2.0/std::sqrt(8),2.0/std::sqrt(8));
		CHECK( Math::Normalize(constructor1) == testingNormalize );
	}

	SECTION("operators inside of the Vector2 struct using float") {
		CHECK( (constructor1[0] == Approx(2.0) && constructor1[1] == Approx(2.0)) );

		Math::Vector2f testingNegation(-2.0);
		CHECK( -constructor1 == testingNegation );

		constructor1 = 2.0;
		Math::Vector2f testingPlusEquals(4.0,5.5);
		CHECK( (constructor1 += constructor2) == testingPlusEquals);

		constructor1 = 2.0;
		Math::Vector2f testingMinusEquals(0.0,-1.5);
		CHECK( (constructor1 -= constructor2) == testingMinusEquals);

		constructor1 = 2.0;
		Math::Vector2f testingTimesEquals(4.0,7.0);
		CHECK( (constructor1 *= constructor2) == testingTimesEquals);

		constructor1 = 2.0;
		Math::Vector2f testingDivideEquals(1.0,2.0/3.5);
		CHECK( (constructor1 /= constructor2) == testingDivideEquals);

		constructor1 = 2.0;
		Math::Vector2f testingPlusEqualsConst(3.0,3.0);
		CHECK( (constructor1 + 1.0f) == testingPlusEqualsConst );
	}
}

TEST_CASE( "Vector3 methods work correctly with int", "[math][vector][vector-3]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector3i constructor1(2);
	Math::Vector3i constructor2(2,3,4);
	Math::Vector3i constructor3(constructor1);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );

	SECTION("methods outside of the Vector3 struct using int") {
		CHECK( Math::toString(constructor1) == "(2, 2, 2)" );
		CHECK( Math::toString(constructor2) == "(2, 3, 4)" );

		REQUIRE( Math::Length(constructor1) == 3 ); //real 3.4, should truncate to maintain type
		REQUIRE( Math::LengthSq(constructor1) == 12 );

		CHECK( Math::Dot(constructor1,constructor1) == 12 );
		CHECK( Math::Cross(constructor1,constructor1) == 0 );
		Math::Vector3i testingCrossProd(2,-4, 2);
		CHECK( Math::Cross(constructor1,constructor2) == testingCrossProd );
	}

	SECTION("operators inside of the Vector3 struct using int") {
		CHECK( (constructor1[0] == 2 && constructor1[1] == 2) );
		CHECK( (constructor2[0] == 2 && constructor2[1] == 3) );

		Math::Vector3i testingNegation(-2);
		CHECK( -constructor1 == testingNegation );

		constructor1 = 2;
		Math::Vector3i testingPlusEquals(4,5,6);
		CHECK( (constructor1 += constructor2) == testingPlusEquals);

		constructor1 = 2;
		Math::Vector3i testingMinusEquals(0,-1, -2);
		CHECK( (constructor1 -= constructor2) == testingMinusEquals);

		constructor1 = 2;
		Math::Vector3i testingTimesEquals(4,6,8);
		CHECK( (constructor1 *= constructor2) == testingTimesEquals);

		constructor1 = 2;
		Math::Vector3i testingDivideEquals(1,0,0); //integer division
		CHECK( (constructor1 /= constructor2) == testingDivideEquals);

		constructor1 = 2;
		Math::Vector3i testingPlusEqualsConst(3,3,3);
		CHECK( (constructor1 += 1) == testingPlusEqualsConst );
	}
}

TEST_CASE( "Vector3 methods work correctly with float", "[math][vector][vector-3]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector3f constructor1(2.0);
	Math::Vector3f constructor2(2.0,3.5,4.5);
	Math::Vector3f constructor3(constructor1);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );

	SECTION("methods outside of the Vector3 struct using float") {
		CHECK( Math::toString(constructor1) == "(2.000000, 2.000000, 2.000000)" );
		CHECK( Math::toString(constructor2) == "(2.000000, 3.500000, 4.500000)" );

		REQUIRE( Math::Length(constructor1) == Approx(std::sqrt(12.0)) );
		REQUIRE( Math::LengthSq(constructor1) == Approx(12.0) );
		REQUIRE( Math::Length(constructor2) == Approx(std::sqrt(2.0*2.0 + 3.5*3.5 + 4.5*4.5)) );
		REQUIRE( Math::LengthSq(constructor2) == Approx(2.0*2.0 + 3.5*3.5 + 4.5*4.5) );

		CHECK( Math::Dot(constructor1,constructor1) == Approx(12.0) );
		CHECK( Math::Dot(constructor1,constructor2) == Approx(20.0) );

		CHECK( Math::Cross(constructor1,constructor1) == 0.0 ); //cross with self is zero
		Math::Vector3f testingCrossProd(2.0,-5.0, 3.0);
		CHECK( Math::Cross(constructor1,constructor2) == testingCrossProd );

		float len = Math::Length(constructor1);
		Math::Vector3f testingNormalize(2.0/len,2.0/len, 2.0/len);
		CHECK( Math::Normalize(constructor1) == testingNormalize );

		len = Math::Length(constructor2);
		Math::Vector3f testingNormalize2(2.0/len,3.5/len, 4.5/len);
		CHECK( Math::Normalize(constructor2) == testingNormalize2 );
	}

	SECTION("operators inside of the Vector3 struct using float") {
		CHECK( (constructor1[0] == Approx(2.0) && constructor1[1] == Approx(2.0)) );
		CHECK( (constructor2[0] == Approx(2.0) && constructor2[1] == Approx(3.5)) );

		Math::Vector3f testingNegation(-2.0);
		CHECK( -constructor1 == testingNegation );

		constructor1 = 2.0;
		Math::Vector3f testingPlusEquals(4.0,5.5,6.5);
		CHECK( (constructor1 += constructor2) == testingPlusEquals);

		constructor1 = 2.0;
		Math::Vector3f testingMinusEquals(0.0,-1.5,-2.5);
		CHECK( (constructor1 -= constructor2) == testingMinusEquals);

		constructor1 = 2.0;
		Math::Vector3f testingTimesEquals(4.0,7.0,9.0);
		CHECK( (constructor1 *= constructor2) == testingTimesEquals);

		constructor1 = 2.0;
		Math::Vector3f testingDivideEquals(1.0,2.0/3.5,2.0/4.5);
		CHECK( (constructor1 /= constructor2) == testingDivideEquals);

		constructor1 = 2.0;
		Math::Vector3f testingPlusEqualsConst(3.0);
		CHECK( (constructor1 + 1.0f) == testingPlusEqualsConst ); //freaking hell
	}
}

TEST_CASE( "Vector4 methods work correctly with int", "[math][vector][vector-4]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector4i constructor1(2);
	Math::Vector4i constructor2(2,3,4,5);
	Math::Vector4i constructor3(constructor1);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );

	SECTION("methods outside of the Vector4 struct using int") {
		CHECK( Math::toString(constructor1) == "(2, 2, 2, 2)" );
		CHECK( Math::toString(constructor2) == "(2, 3, 4, 5)" );

		REQUIRE( Math::Length(constructor1) == 4 );
		REQUIRE( Math::LengthSq(constructor1) == 16 );

		CHECK( Math::Dot(constructor1,constructor1) == 16 );
	}

	SECTION("operators inside of the Vector4 struct using int") {
		CHECK( (constructor1[0] == 2 && constructor1[1] == 2) );
		CHECK( (constructor2[0] == 2 && constructor2[1] == 3) );

		Math::Vector4i testingNegation(-2);
		CHECK( -constructor1 == testingNegation );

		constructor1 = 2;
		Math::Vector4i testingPlusEquals(4,5,6,7);
		CHECK( (constructor1 += constructor2) == testingPlusEquals);

		constructor1 = 2;
		Math::Vector4i testingMinusEquals(0,-1,-2,-3);
		CHECK( (constructor1 -= constructor2) == testingMinusEquals);

		constructor1 = 2;
		Math::Vector4i testingTimesEquals(4,6,8,10);
		CHECK( (constructor1 *= constructor2) == testingTimesEquals);

		constructor1 = 2;
		Math::Vector4i testingDivideEquals(1,0,0,0); //integer division
		CHECK( (constructor1 /= constructor2) == testingDivideEquals);

		constructor1 = 2;
		Math::Vector4i testingPlusEqualsConst(3,3,3,3);
		CHECK( (constructor1 += 1) == testingPlusEqualsConst );
	}
}

TEST_CASE( "Vector4 methods work correctly with float", "[math][vector][vector-4]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector4f constructor1(2.0);
	Math::Vector4f constructor2(2.0,3.5,4.5,5.5);
	Math::Vector4f constructor3(constructor1);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );

	SECTION("methods outside of the Vector4 struct using float") {
		CHECK( Math::toString(constructor1) == "(2.000000, 2.000000, 2.000000, 2.000000)" );
		CHECK( Math::toString(constructor2) == "(2.000000, 3.500000, 4.500000, 5.500000)" );

		REQUIRE( Math::Length(constructor1) == Approx(std::sqrt(16.0)) );
		REQUIRE( Math::LengthSq(constructor1) == Approx(16.0) );
		REQUIRE( Math::Length(constructor2) == Approx(std::sqrt(2.0*2.0 + 3.5*3.5 + 4.5*4.5 + 5.5*5.5)) );
		REQUIRE( Math::LengthSq(constructor2) == Approx(2.0*2.0 + 3.5*3.5 + 4.5*4.5 + 5.5*5.5) );

		CHECK( Math::Dot(constructor1,constructor1) == Approx(16.0) );
		CHECK( Math::Dot(constructor1,constructor2) == Approx(31.0) );

		float len = Math::Length(constructor1);
		Math::Vector4f testingNormalize(2.0/len,2.0/len, 2.0/len, 2.0/len);
		CHECK( Math::Normalize(constructor1) == testingNormalize );

		len = Math::Length(constructor2);
		Math::Vector4f testingNormalize2(2.0/len,3.5/len, 4.5/len, 5.5/len);
		Math::Vector4f norm = Math::Normalize(constructor2);
		CHECK( vectorFuzzyEquals(norm,testingNormalize2) );
	}

	SECTION("operators inside of the Vector4 struct using float") {
		CHECK( (constructor1[0] == Approx(2.0) && constructor1[1] == Approx(2.0)) );
		CHECK( (constructor2[0] == Approx(2.0) && constructor2[1] == Approx(3.5)) );

		Math::Vector4f testingNegation(-2.0);
		CHECK( -constructor1 == testingNegation );

		constructor1 = 2.0;
		Math::Vector4f testingPlusEquals(4.0,5.5,6.5,7.5);
		CHECK( (constructor1 += constructor2) == testingPlusEquals);

		constructor1 = 2.0;
		Math::Vector4f testingMinusEquals(0.0,-1.5,-2.5,-3.5);
		CHECK( (constructor1 -= constructor2) == testingMinusEquals);

		constructor1 = 2.0;
		Math::Vector4f testingTimesEquals(4.0,7.0,9.0,11.0);
		CHECK( (constructor1 *= constructor2) == testingTimesEquals);

		constructor1 = 2.0;
		Math::Vector4f testingDivideEquals(1.0,2.0/3.5,2.0/4.5,2.0/5.5);
		CHECK( (constructor1 /= constructor2) == testingDivideEquals);

		constructor1 = 2.0;
		Math::Vector4f testingPlusEqualsConst(3.0);
		CHECK( (constructor1 + 1.0f) == testingPlusEqualsConst );
	}
}

//************************* Matrices *************************
TEST_CASE( "Matrix2 methods work correctly with int", "[math][matrix][matrix-3]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Matrix2i constructor1(2);
	Math::Matrix2i constructor2(2,3);
	Math::Matrix2i constructor3(constructor1);

	Math::Vector2i testingConstructor4(2);
	Math::Matrix2i constructor4(testingConstructor4,testingConstructor4);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );
	REQUIRE( constructor1 == constructor4 );

	SECTION("methods outside of the Matrix2 struct using int") {
		Math::Vector2i v1(1,2);
		Math::Vector2i v2(3,10);
		Math::Matrix2i test(v1,v2);

		REQUIRE( Math::Determinant(test) == 4 );

		Math::Vector2i v3(1,3);
		Math::Vector2i v4(2,10);
		Math::Matrix2i test2(v3,v4);

		REQUIRE( Math::Transpose(test) == test2 );

		Math::Vector2i v5(10/4,-2/4);
		Math::Vector2i v6(-3/4,1/4);
		Math::Matrix2i test3(v5,v6);

		REQUIRE( Math::Inverse(test) == test3 ); //int type truncates

		CHECK( constructor1 * constructor1 == Math::Matrix2i(8) ); //matrix * matrix
		CHECK( constructor1 * testingConstructor4 == Math::Vector2i(8) ); //matrix * vector
		CHECK( constructor1 - constructor1 == Math::Matrix2i(0) );
		CHECK( constructor1 + constructor1 == Math::Matrix2i(4) );

		//Matrix math with scalar
		CHECK( constructor1 - 1 == Math::Matrix2i(1) );
		CHECK( constructor1 + 1 == Math::Matrix2i(3) );
		CHECK( constructor1 * 2 == Math::Matrix2i(4) );
		CHECK( constructor1 / 2 == Math::Matrix2i(1) );
	}

	SECTION("operators inside of the Matrix2 struct using int") {
		REQUIRE( constructor1[0] == constructor1[0] );
		CHECK( (constructor1[0] == Math::Vector2i(2) && constructor1[1] == Math::Vector2i(2)) );
		CHECK( (constructor2[0] == Math::Vector2i(2) && constructor2[1] == Math::Vector2i(3)) );
		CHECK( (constructor2[0][0] == 2 && constructor2[1][0] == 3) );

		Math::Matrix2i testingAssignment(0);
		testingAssignment = constructor1; //testing that assignment doesn't copy reference
		constructor1[0][0] = 3;
		CHECK( testingAssignment[0][0] != constructor1[0][0] );

		constructor1 = 2;
		Math::Matrix2i testingConstMult(4);
		constructor1 *= 2;
		CHECK( constructor1 == testingConstMult );

		constructor1 = 2;
		Math::Matrix2i testingMatrixAdd(4);
		constructor1 += constructor1;
		CHECK( constructor1 == testingMatrixAdd );

		constructor1 = 2;
		Math::Matrix2i testingMatrixSub(0);
		constructor1 -= constructor1;
		CHECK( constructor1 == testingMatrixSub );

		constructor1 = 2;
		Math::Matrix2i testingNegate(-2);
		CHECK( constructor1 == -testingNegate );
	}
}

TEST_CASE( "Matrix2 methods work correctly with float", "[math][matrix][matrix-3]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Matrix2f constructor1(2.0);
	Math::Matrix2f constructor2(2.0,3.0);
	Math::Matrix2f constructor3(constructor1);

	Math::Vector2f testingConstructor4(2.0);
	Math::Matrix2f constructor4(testingConstructor4,testingConstructor4);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );
	REQUIRE( constructor1 == constructor4 );

	SECTION("methods outside of the Matrix2 struct using float") {
		Math::Vector2f v1(1.0,2.0);
		Math::Vector2f v2(3.0,10.0);
		Math::Matrix2f test(v1,v2);

		REQUIRE( Math::Determinant(test) == 4.0 );

		Math::Vector2f v3(1.0,3.0);
		Math::Vector2f v4(2.0,10.0);
		Math::Matrix2f test2(v3,v4);

		REQUIRE( Math::Transpose(test) == test2 );

		Math::Vector2f v5(10.0/4,-2.0/4);
		Math::Vector2f v6(-3.0/4,1.0/4);
		Math::Matrix2f test3(v5,v6);

		Math::Matrix2f inv = Math::Inverse(test);
		REQUIRE( matrixFuzzyEquals(inv,test3) ); //inverse correct

		CHECK( constructor1 * constructor1 == Math::Matrix2f(8.0) ); //matrix * matrix
		CHECK( constructor1 * testingConstructor4 == Math::Vector2f(8.0) ); //matrix * vector
		CHECK( constructor1 - constructor1 == Math::Matrix2f(0.0) );
		CHECK( constructor1 + constructor1 == Math::Matrix2f(4.0) );

		//Matrix math with scalar
		CHECK( constructor1 - 1.0 == Math::Matrix2f(1.0) );
		CHECK( constructor1 + 1.0 == Math::Matrix2f(3.0) );
		CHECK( constructor1 * 2.0 == Math::Matrix2f(4.0) );
		CHECK( constructor1 / 2.0 == Math::Matrix2f(1.0) );
	}

	SECTION("operators inside of the Matrix2 struct using float") {
		REQUIRE( constructor1[0] == constructor1[0] );
		CHECK( (constructor1[0] == Math::Vector2f(2.0) && constructor1[1] == Math::Vector2f(2.0)) );
		CHECK( (constructor2[0] == Math::Vector2f(2.0) && constructor2[1] == Math::Vector2f(3.0)) );
		CHECK( (constructor2[0][0] == 2.0 && constructor2[1][0] == 3.0) );

		Math::Matrix2f testingAssignment(0.0);
		testingAssignment = constructor1; //testing that assignment doesn't copy reference
		constructor1[0][0] = 3.0;
		CHECK( testingAssignment[0][0] != constructor1[0][0] );

		constructor1 = 2.0;
		Math::Matrix2f testingConstMult(4.0);
		constructor1 *= 2.0;
		CHECK( constructor1 == testingConstMult );

		constructor1 = 2.0;
		Math::Matrix2f testingMatrixAdd(4.0);
		constructor1 += constructor1;
		CHECK( constructor1 == testingMatrixAdd );

		constructor1 = 2.0;
		Math::Matrix2f testingMatrixSub(0.0);
		constructor1 -= constructor1;
		CHECK( constructor1 == testingMatrixSub );

		Math::Vector2f v1(1.0,7.0);
		Math::Vector2f v2(4.0,3.0);
		Math::Matrix2f m1(v1,v2);
		Math::Vector2f v3(1.0,2.0);
		Math::Vector2f v4(4.0,5.0);
		Math::Matrix2f m2(v3,v4);

		Math::Vector2f v5(1.0,-29.0/3);
		Math::Vector2f v6(0.0,25.0/3);
		Math::Matrix2f testingMatrixDiv(v5,v6);

		m1 /= m2;
		CHECK( matrixFuzzyEquals(m1,testingMatrixDiv) );

		constructor1 = 2.0;
		Math::Matrix2f testingNegate(-2.0);
		CHECK( constructor1 == -testingNegate );
	}
}

TEST_CASE( "Matrix3 methods work correctly with int", "[math][matrix][matrix-3]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Matrix3i constructor1(2);
	Math::Matrix3i constructor2(2,3,4);
	Math::Matrix3i constructor3(constructor1);

	Math::Vector3i testingConstructor4(2);
	Math::Matrix3i constructor4(testingConstructor4,testingConstructor4,testingConstructor4);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );
	REQUIRE( constructor1 == constructor4 );

	SECTION("methods outside of the Matrix3 struct using int") {
		Math::Vector3i v1(1,2,3);
		Math::Vector3i v2(2,10,4);
		Math::Vector3i v3(4,5,6);
		Math::Matrix3i test(v1,v2,v3);

		REQUIRE( Math::Determinant(test) == -42 );

		Math::Vector3i v4(1,2,4);
		Math::Vector3i v5(2,10,5);
		Math::Vector3i v6(3,4,6);
		Math::Matrix3i test2(v4,v5,v6);

		REQUIRE( Math::Transpose(test) == test2 );

		Math::Vector3i v7(-20/21,-1/14,11/21);
		Math::Vector3i v8(-2/21,1/7,-1/21);
		Math::Vector3i v9(5/7,-1/14,-1/7);
		Math::Matrix3i test3(v7,v8,v9);

		REQUIRE( Math::Inverse(test) == 0 ); //zero because inverse can't represent with int

		CHECK( constructor1 * constructor1 == Math::Matrix3i(12) ); //matrix * matrix
		CHECK( constructor1 * testingConstructor4 == Math::Vector3i(12) ); //matrix * vector
		CHECK( constructor1 - constructor1 == Math::Matrix3i(0) );
		CHECK( constructor1 + constructor1 == Math::Matrix3i(4) );

		//Matrix math with scalar
		CHECK( constructor1 - 1 == Math::Matrix3i(1) );
		CHECK( constructor1 + 1 == Math::Matrix3i(3) );
		CHECK( constructor1 * 2 == Math::Matrix3i(4) );
		CHECK( constructor1 / 2 == Math::Matrix3i(1) );
	}

	SECTION("operators inside of the Matrix3 struct using int") {
		REQUIRE( constructor1[0] == constructor1[0] );
		CHECK( (constructor1[0] == Math::Vector3i(2) && constructor1[1] == Math::Vector3i(2) && constructor1[2] == Math::Vector3i(2)) );
		CHECK( (constructor2[0] == Math::Vector3i(2) && constructor2[1] == Math::Vector3i(3) && constructor2[2] == Math::Vector3i(4)) );
		CHECK( (constructor2[0][0] == 2 && constructor2[1][0] == 3 && constructor2[2][0] == 4) );

		Math::Matrix3i testingAssignment(0);
		testingAssignment = constructor1; //testing that assignment doesn't copy reference
		constructor1[0][0] = 3;
		CHECK( testingAssignment[0][0] != constructor1[0][0] );

		constructor1 = 2;
		Math::Matrix3i testingConstMult(4);
		constructor1 *= 2;
		CHECK( constructor1 == testingConstMult );

		constructor1 = 2;
		Math::Matrix3i testingMatrixAdd(4);
		constructor1 += constructor1;
		CHECK( constructor1 == testingMatrixAdd );

		constructor1 = 2;
		Math::Matrix3i testingMatrixSub(0);
		constructor1 -= constructor1;
		CHECK( constructor1 == testingMatrixSub );

		Math::Vector3i v1(1,7,7);
		Math::Vector3i v2(4,3,2);
		Math::Vector3i v3(3,4,3);
		Math::Matrix3i m1(v1,v2,v3);
		Math::Vector3i v4(1,2,4);
		Math::Vector3i v5(4,5,6);
		Math::Vector3i v6(1,7,3);
		Math::Matrix3i m2(v4,v5,v6);

		Math::Vector3i v7(37/53,-155/53,-169/53);
		Math::Vector3i v8(20/53,-5/53,-14/53);
		Math::Vector3i v9(-6/53,134/53,142/53);
		Math::Matrix3i testingMatrixDiv(v7,v8,v9);

		m1 /= m2;
		CHECK( m1 == 0 );  //zero because inverse can't represent with int

		constructor1 = 2;
		Math::Matrix3i testingNegate(-2);
		CHECK( constructor1 == -testingNegate );
	}
}

TEST_CASE( "Matrix3 methods work correctly with float", "[math][matrix][matrix-3]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Matrix3f constructor1(2.0);
	Math::Matrix3f constructor2(2.0,3.0,4.0);
	Math::Matrix3f constructor3(constructor1);

	Math::Vector3f testingConstructor4(2.0);
	Math::Matrix3f constructor4(testingConstructor4,testingConstructor4,testingConstructor4);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );
	REQUIRE( constructor1 == constructor4 );

	SECTION("methods outside of the Matrix3 struct using float") {
		Math::Vector3f v1(1.0,2.0,3.0);
		Math::Vector3f v2(2.0,10.0,4.0);
		Math::Vector3f v3(4.0,5.0,6.0);
		Math::Matrix3f test(v1,v2,v3);

		REQUIRE( Math::Determinant(test) == -42.0 );

		Math::Vector3f v4(1.0,2.0,4.0);
		Math::Vector3f v5(2.0,10.0,5.0);
		Math::Vector3f v6(3.0,4.0,6.0);
		Math::Matrix3f test2(v4,v5,v6);

		REQUIRE( Math::Transpose(test) == test2 );

		Math::Vector3f v7(-20.0/21,-1.0/14,11.0/21);
		Math::Vector3f v8(-2.0/21,1.0/7,-1.0/21);
		Math::Vector3f v9(5.0/7,-1.0/14,-1.0/7);
		Math::Matrix3f test3(v7,v8,v9);

		Math::Matrix3f inv = Math::Inverse(test);
		REQUIRE( matrixFuzzyEquals(inv,test3) ); //inverse correct

		CHECK( constructor1 * constructor1 == Math::Matrix3f(12.0) ); //matrix * matrix
		CHECK( constructor1 * testingConstructor4 == Math::Vector3f(12.0) ); //matrix * vector
		CHECK( constructor1 - constructor1 == Math::Matrix3f(0.0) );
		CHECK( constructor1 + constructor1 == Math::Matrix3f(4.0) );

		//Matrix math with scalar
		CHECK( constructor1 - 1.0 == Math::Matrix3f(1.0) );
		CHECK( constructor1 + 1.0 == Math::Matrix3f(3.0) );
		CHECK( constructor1 * 2.0 == Math::Matrix3f(4.0) );
		CHECK( constructor1 / 2.0 == Math::Matrix3f(1.0) );
	}

	SECTION("operators inside of the Matrix3 struct using float") {
		REQUIRE( constructor1[0] == constructor1[0] );
		CHECK( (constructor1[0] == Math::Vector3f(2.0) && constructor1[1] == Math::Vector3f(2.0) && constructor1[2] == Math::Vector3f(2.0)) );
		CHECK( (constructor2[0] == Math::Vector3f(2.0) && constructor2[1] == Math::Vector3f(3.0) && constructor2[2] == Math::Vector3f(4.0)) );
		CHECK( (constructor2[0][0] == 2.0 && constructor2[1][0] == 3.0 && constructor2[2][0] == 4.0) );

		Math::Matrix3f testingAssignment(0.0);
		testingAssignment = constructor1; //testing that assignment doesn't copy reference
		constructor1[0][0] = 3.0;
		CHECK( testingAssignment[0][0] != constructor1[0][0] );

		constructor1 = 2.0;
		Math::Matrix3f testingConstMult(4.0);
		constructor1 *= 2.0;
		CHECK( constructor1 == testingConstMult );

		constructor1 = 2.0;
		Math::Matrix3f testingMatrixAdd(4.0);
		constructor1 += constructor1;
		CHECK( constructor1 == testingMatrixAdd );

		constructor1 = 2.0;
		Math::Matrix3f testingMatrixSub(0.0);
		constructor1 -= constructor1;
		CHECK( constructor1 == testingMatrixSub );

		Math::Vector3f v1(1.0,7.0,7.0);
		Math::Vector3f v2(4.0,3.0,2.0);
		Math::Vector3f v3(3.0,4.0,3.0);
		Math::Matrix3f m1(v1,v2,v3);
		Math::Vector3f v4(1.0,2.0,4.0);
		Math::Vector3f v5(4.0,5.0,6.0);
		Math::Vector3f v6(1.0,7.0,3.0);
		Math::Matrix3f m2(v4,v5,v6);

		Math::Vector3f v7(37.0/53,-155.0/53,-169.0/53);
		Math::Vector3f v8(20.0/53,-5.0/53,-14.0/53);
		Math::Vector3f v9(-6.0/53,134.0/53,142.0/53);
		Math::Matrix3f testingMatrixDiv(v7,v8,v9);

		m1 /= m2;
		CHECK( matrixFuzzyEquals(m1,testingMatrixDiv) );

		constructor1 = 2.0;
		Math::Matrix3f testingNegate(-2.0);
		CHECK( constructor1 == -testingNegate );
	}
}

TEST_CASE( "Matrix4 methods work correctly with int", "[math][matrix][matrix-4]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Matrix4i constructor1(2);
	Math::Matrix4i constructor2(2,3,4,5);
	Math::Matrix4i constructor3(constructor1);

	Math::Vector4i testingConstructor4(2);
	Math::Matrix4i constructor4(testingConstructor4,testingConstructor4,testingConstructor4,testingConstructor4);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );
	REQUIRE( constructor1 == constructor4 );

	SECTION("methods outside of the Matrix4 struct using int") {
		Math::Vector4i v1(2,1,-3,0);
		Math::Vector4i v2(-1,2,1,1);
		Math::Vector4i v3(0,-4,-2,4);
		Math::Vector4i v4(3,0,5,3);
		Math::Matrix4i test(v1,v2,v3,v4);

		REQUIRE( Math::Determinant(test) == -308 );

		Math::Vector4i v5(2,-1,0,3);
		Math::Vector4i v6(1,2,-4,0);
		Math::Vector4i v7(-3,1,-2,5);
		Math::Vector4i v8(0,1,4,3);
		Math::Matrix4i test2(v5,v6,v7,v8);

		REQUIRE( Math::Transpose(test) == test2 );

		REQUIRE( Math::Inverse(test) == 0 ); //zero because inverse can't represent with int

		CHECK( constructor1 * constructor1 == Math::Matrix4i(16) ); //matrix * matrix
		CHECK( constructor1 * testingConstructor4 == Math::Vector4i(16) ); //matrix * vector
		CHECK( constructor1 - constructor1 == Math::Matrix4i(0) );
		CHECK( constructor1 + constructor1 == Math::Matrix4i(4) );

		//Matrix math with scalar
		CHECK( constructor1 - 1 == Math::Matrix4i(1) );
		CHECK( constructor1 + 1 == Math::Matrix4i(3) );
		CHECK( constructor1 * 2 == Math::Matrix4i(4) );
		CHECK( constructor1 / 2 == Math::Matrix4i(1) );
	}

	SECTION("operators inside of the Matrix4 struct using int") {
		REQUIRE( constructor1[0] == constructor1[0] );
		CHECK( (constructor1[0] == Math::Vector4i(2) && constructor1[1] == Math::Vector4i(2) && constructor1[2] == Math::Vector4i(2) && constructor1[3] == Math::Vector4i(2)) );
		CHECK( (constructor2[0] == Math::Vector4i(2) && constructor2[1] == Math::Vector4i(3) && constructor2[2] == Math::Vector4i(4) && constructor2[3] == Math::Vector4i(5)) );
		CHECK( (constructor2[0][0] == 2 && constructor2[1][0] == 3 && constructor2[2][0] == 4 && constructor2[3][0] == 5) );

		Math::Matrix4i testingAssignment(0);
		testingAssignment = constructor1; //testing that assignment doesn't copy reference
		constructor1[0][0] = 3;
		CHECK( testingAssignment[0][0] != constructor1[0][0] );

		constructor1 = 2;
		Math::Matrix4i testingConstMult(4);
		constructor1 *= 2;
		CHECK( constructor1 == testingConstMult );

		constructor1 = 2;
		Math::Matrix4i testingMatrixAdd(4);
		constructor1 += constructor1;
		CHECK( constructor1 == testingMatrixAdd );

		constructor1 = 2;
		Math::Matrix4i testingMatrixSub(0);
		constructor1 -= constructor1;
		CHECK( constructor1 == testingMatrixSub );

		constructor1 = 2;
		Math::Matrix4i testingNegate(-2);
		CHECK( constructor1 == -testingNegate );
	}
}

TEST_CASE( "Matrix4 methods work correctly with float", "[math][matrix][matrix-4]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Matrix4f constructor1(2.0);
	Math::Matrix4f constructor2(2.0,3.0,4.0,5.0);
	Math::Matrix4f constructor3(constructor1);

	Math::Vector4f testingConstructor4(2.0);
	Math::Matrix4f constructor4(testingConstructor4,testingConstructor4,testingConstructor4,testingConstructor4);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );
	REQUIRE( constructor1 == constructor4 );

	SECTION("methods outside of the Matrix4 struct using float") {
		Math::Vector4f v1(2.0,1.0,-3.0,0.0);
		Math::Vector4f v2(-1.0,2.0,1.0,1.0);
		Math::Vector4f v3(0.0,-4.0,-2.0,4.0);
		Math::Vector4f v4(3.0,0.0,5.0,3.0);
		Math::Matrix4f test(v1,v2,v3,v4);

		REQUIRE( Math::Determinant(test) == -308.0 );

		Math::Vector4f v5(2.0,-1.0,0.0,3.0);
		Math::Vector4f v6(1.0,2.0,-4.0,0.0);
		Math::Vector4f v7(-3.0,1.0,-2.0,5.0);
		Math::Vector4f v8(0.0,1.0,4.0,3.0);
		Math::Matrix4f test2(v5,v6,v7,v8);

		REQUIRE( Math::Transpose(test) == test2 );

		Math::Vector4f v9(60.0/308,-62.0/308,-16.0/308,42.0/308);
		Math::Vector4f v10(44.0/308,88.0/308,-22.0/308,0);
		Math::Vector4f v11(-48.0/308,-12.0/308,-18.0/308,28.0/308);
		Math::Vector4f v12(20.0/308,82.0/308,46.0/308,14.0/308);
		Math::Matrix4f test3(v9,v10,v11,v12);

		Math::Matrix4f inv = Math::Inverse(test);
		REQUIRE( matrixFuzzyEquals(inv,test3) ); //zero because inverse can't represent with int

		CHECK( constructor1 * constructor1 == Math::Matrix4f(16.0) ); //matrix * matrix
		CHECK( constructor1 * testingConstructor4 == Math::Vector4f(16.0) ); //matrix * vector
		CHECK( constructor1 - constructor1 == Math::Matrix4f(0.0) );
		CHECK( constructor1 + constructor1 == Math::Matrix4f(4.0) );

		//Matrix math with scalar
		CHECK( constructor1 - 1 == Math::Matrix4f(1.0) );
		CHECK( constructor1 + 1 == Math::Matrix4f(3.0) );
		CHECK( constructor1 * 2 == Math::Matrix4f(4.0) );
		CHECK( constructor1 / 2 == Math::Matrix4f(1.0) );
	}

	SECTION("operators inside of the Matrix4 struct using float") {
		REQUIRE( constructor1[0] == constructor1[0] );
		CHECK( (constructor1[0] == Math::Vector4f(2.0) && constructor1[1] == Math::Vector4f(2.0) && constructor1[2] == Math::Vector4f(2.0) && constructor1[3] == Math::Vector4f(2.0)) );
		CHECK( (constructor2[0] == Math::Vector4f(2.0) && constructor2[1] == Math::Vector4f(3.0) && constructor2[2] == Math::Vector4f(4.0) && constructor2[3] == Math::Vector4f(5.0)) );
		CHECK( (constructor2[0][0] == 2.0 && constructor2[1][0] == 3.0 && constructor2[2][0] == 4.0 && constructor2[3][0] == 5.0) );

		Math::Matrix4f testingAssignment(0);
		testingAssignment = constructor1; //testing that assignment doesn't copy reference
		constructor1[0][0] = 3.0;
		CHECK( testingAssignment[0][0] != constructor1[0][0] );

		constructor1 = 2.0;
		Math::Matrix4f testingConstMult(4.0);
		constructor1 *= 2.0;
		CHECK( constructor1 == testingConstMult );

		constructor1 = 2.0;
		Math::Matrix4f testingMatrixAdd(4.0);
		constructor1 += constructor1;
		CHECK( constructor1 == testingMatrixAdd );

		constructor1 = 2.0;
		Math::Matrix4f testingMatrixSub(0.0);
		constructor1 -= constructor1;
		CHECK( constructor1 == testingMatrixSub );

		constructor1 = 2.0;
		Math::Matrix4f testingNegate(-2.0);
		CHECK( constructor1 == -testingNegate );
	}
}

//************************* Quaternion *************************
TEST_CASE( "Quaternion methods work correctly with float", "[math][Quaternion]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Quaternionf constructor1(2.0,3.5,4.5,5.5);
	Math::Vector3f testingConstructor2(2);
	Math::Quaternionf constructor2(testingConstructor2,3);
	Math::Quaternionf constructor3(constructor1);

	REQUIRE( constructor1 == constructor1 );
	REQUIRE( constructor1 != constructor2 );
	REQUIRE( constructor2 == constructor2 );
	REQUIRE( constructor1 == constructor3 );

	SECTION("methods outside of the Quaternion struct using float") {
		REQUIRE( Math::Length(constructor1) == Approx(std::sqrt(2.0*2.0 + 3.5*3.5 + 4.5*4.5 + 5.5*5.5)) );
		REQUIRE( Math::LengthSq(constructor1) == Approx(2.0*2.0 + 3.5*3.5 + 4.5*4.5 + 5.5*5.5) );

		float len = Math::Length(constructor2);
		Math::Quaternionf testingNormalize(2.0/len,2.0/len, 2.0/len, 3.0/len);
		CHECK( quaternionFuzzyEquals(Math::Normalize(constructor2), testingNormalize) );

		len = Math::Length(constructor1);
		Math::Quaternionf testingNormalize2(2.0/len,3.5/len, 4.5/len, 5.5/len);
		Math::Quaternionf norm = Math::Normalize(constructor1);
		CHECK( vectorFuzzyEquals(norm,testingNormalize2) );
	}

	SECTION("operators inside of the Quaternion struct using float") {
		CHECK( (constructor2[0] == Approx(2.0) && constructor2[1] == Approx(2.0) && constructor2[2] == Approx(2.0) && constructor2[3] == Approx(3.0)) );
		CHECK( (constructor1[0] == Approx(2.0) && constructor1[1] == Approx(3.5) && constructor1[2] == Approx(4.5) && constructor1[3] == Approx(5.5)) );

		Math::Quaternionf testingNegation(-testingConstructor2,-3);
		CHECK( -constructor2 == testingNegation );
		Math::Quaternionf reset(testingConstructor2,3);
		constructor2 = reset;
		Math::Quaternionf testingTimesEquals(19.0,16.5,27.5,-3.5);
		CHECK( (constructor2 *= constructor1) == testingTimesEquals );
	}

	SECTION("Quaternion conversions with euler and rotation matrices") {
		double M_PI = 3.141592653589793;
		Math::Vector3f v1(M_PI/4.0,0,M_PI/4.0);
		Math::Quaternionf testingEulerToQuat(0.3535533328235472,0.1464465516370091,0.3535533328235472,0.853553448362991);

		//Test converting euler angles ZYX to quaternion
		Math::Quaternionf convertedEuler = Math::Quaternionf::FromEuler(v1);
		REQUIRE( quaternionFuzzyEquals(convertedEuler,testingEulerToQuat) );

		//Test converting quaternion back to euler angles ZYX
		REQUIRE( vectorFuzzyEquals(Math::Quaternionf::ToEuler(convertedEuler),v1) );

		//Test converting quaternion to rotation matrix
		Math::Vector3f r1(0.7071065431725605,0.7071070192004545,5.551115123125783e-17);
		Math::Vector3f r2(-0.49999999999988676,0.49999966339744806,0.7071070192004545);
		Math::Vector3f r3(0.5000003366025518,-0.49999999999988676,0.7071065431725605);
		Math::Matrix3f rotationMatrix(r1,r2,r3);
		Math::Quaternionf q = testingEulerToQuat;
		Math::Matrix3f generatedRotationMatrix = Math::Quaternionf::ToRotationMatrix(q);
		REQUIRE( matrixFuzzyEquals(rotationMatrix,generatedRotationMatrix) );
	}

	SECTION("Quaternion conversions with euler and rotation matrices part2") {
		double M_PI = 3.141592653589793;
		Math::Vector3f v1(3.0*M_PI/4.0,M_PI/3.0,M_PI/4.0);
		Math::Quaternionf testingEulerToQuat(0.6659757236952106,0.4829628838882861,-0.29995118873620663,0.4829621854873183);

		//Test converting euler angles ZYX to quaternion
		Math::Quaternionf convertedEuler = Math::Quaternionf::FromEuler(v1);
		REQUIRE( quaternionFuzzyEquals(convertedEuler,testingEulerToQuat) );

		//Test converting quaternion back to euler angles ZYX
		REQUIRE( vectorFuzzyEquals(Math::Quaternionf::ToEuler(convertedEuler),v1) );

		//Test converting quaternion to rotation matrix
		Math::Vector3f r1(0.35355227432409286,0.35355294892773975,-0.866026039807557);
		Math::Vector3f r2(0.9330132755339695,-0.06698876035124601,0.3535515997191588);
		Math::Vector3f r3(0.06698519984022139,-0.9330127642701906,-0.35355362353009934);
		Math::Matrix3f rotationMatrix(r1,r2,r3);
		Math::Quaternionf q = testingEulerToQuat;
		Math::Matrix3f generatedRotationMatrix = Math::Quaternionf::ToRotationMatrix(q);
		REQUIRE( matrixFuzzyEquals(rotationMatrix,generatedRotationMatrix) );
	}
}
#endif
