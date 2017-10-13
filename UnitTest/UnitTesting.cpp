#define DO_UNIT_TESTING 1

#if DO_UNIT_TESTING==1

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch.hpp>
#include <iostream>

#include "Math/VectorMath.h"
#include "Math/MatrixMath.h"

//************************* Vectors *************************
TEST_CASE( "Vector2 methods work correctly with int", "[math][vector][vector-2]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector2i v(2);
	Math::Vector2i vv(2,3);
	Math::Vector2i vvv(v);

	REQUIRE( v == v );
	REQUIRE( v != vv );
	REQUIRE( vv == vv );
	REQUIRE( v == vvv );

	SECTION("methods outside of the Vector2 struct using int") {
		CHECK( Math::toString(v) == "(2, 2)" );
		CHECK( Math::toString(vv) == "(2, 3)" );

		REQUIRE( Math::Length(v) == 2 ); //real 2.8, should truncate to maintain type
		REQUIRE( Math::LengthSq(v) == 8 );

		CHECK( Math::Dot(v,v) == 8 );
		CHECK( Math::Cross(v,v) == 0 );
		Math::Vector2i v2(4,-4);
		CHECK( Math::Cross(v,2) == v2 );
		Math::Vector2i v3(-4,4);
		CHECK( Math::Cross(2,v) == v3 );
	}

	SECTION("operators inside of the Vector2 struct using int") {
		CHECK( (v[0] == 2 && v[1] == 2) );

		Math::Vector2i v2(-2);
		CHECK( -v == v2 );

		v = 2;
		Math::Vector2i v3(4,5);
		CHECK( (v += vv) == v3);

		v = 2;
		Math::Vector2i v4(0,-1);
		CHECK( (v -= vv) == v4);

		v = 2;
		Math::Vector2i v5(4,6);
		CHECK( (v *= vv) == v5);

		v = 2;
		Math::Vector2i v6(1,0); //integer division
		CHECK( (v /= vv) == v6);

		v = 2;
		Math::Vector2i v7(3,3);
		CHECK( (v += 1) == v7 ); //freaking hell
	}
}

TEST_CASE("Vector2 methods work correctly with float", "[math][vector][vector-2]") {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector2f v(2.0);
	Math::Vector2f vv(2.0,3.5);
	Math::Vector2f vvv(v);

	REQUIRE( v == v );
	REQUIRE( v != vv );
	REQUIRE( vv == vv );
	REQUIRE( v == vvv );

	SECTION("methods outside of the Vector2 struct using float") {
		CHECK( Math::toString(v) == "(2.000000, 2.000000)" );
		CHECK( Math::toString(vv) == "(2.000000, 3.500000)" );

		REQUIRE( Math::Length(v) == Approx(std::sqrt(8)) );
		REQUIRE( Math::LengthSq(v) == Approx(8.0) );

		CHECK( Math::Dot(v,v) == Approx(8.0) );
		CHECK( Math::Dot(v,vv) == Approx(11.0) );

		CHECK( Math::Cross(v,v) == Approx(0.0) );
		Math::Vector2f v2(4.0,-4.0);
		CHECK( Math::Cross(v,2.0f) == v2 );
		Math::Vector2f v3(-4.0,4.0);
		CHECK( Math::Cross(2.0f,v) == v3 );

		Math::Vector2f v4(2.0/std::sqrt(8),2.0/std::sqrt(8));
		CHECK( Math::Normalize(v) == v4 );
	}

	SECTION("operators inside of the Vector2 struct using float") {
		CHECK( (v[0] == Approx(2.0) && v[1] == Approx(2.0)) );

		Math::Vector2f v2(-2.0);
		CHECK( -v == v2 );

		v = 2.0;
		Math::Vector2f v3(4.0,5.5);
		CHECK( (v += vv) == v3);

		v = 2.0;
		Math::Vector2f v4(0.0,-1.5);
		CHECK( (v -= vv) == v4);

		v = 2.0;
		Math::Vector2f v5(4.0,7.0);
		CHECK( (v *= vv) == v5);

		v = 2.0;
		Math::Vector2f v6(1.0,2.0/3.5);
		CHECK( (v /= vv) == v6);

		v = 2.0;
		Math::Vector2f v7(3.0,3.0);
		CHECK( (v + 1.0f) == v7 ); //freaking hell
	}
}
//**

TEST_CASE( "Vector3 methods work correctly with int", "[math][vector][vector-3]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector3i v(2);
	Math::Vector3i vv(2,3,4);
	Math::Vector3i vvv(v);

	REQUIRE( v == v );
	REQUIRE( v != vv );
	REQUIRE( vv == vv );
	REQUIRE( v == vvv );

	SECTION("methods outside of the Vector3 struct using int") {
		CHECK( Math::toString(v) == "(2, 2, 2)" );
		CHECK( Math::toString(vv) == "(2, 3, 4)" );

		REQUIRE( Math::Length(v) == 3 ); //real 3.4, should truncate to maintain type
		REQUIRE( Math::LengthSq(v) == 12 );

		CHECK( Math::Dot(v,v) == 12 );
		CHECK( Math::Cross(v,v) == 0 );
		Math::Vector3i v2(2,-4, 2);
		CHECK( Math::Cross(v,vv) == v2 );
	}

	SECTION("operators inside of the Vector3 struct using int") {
		CHECK( (v[0] == 2 && v[1] == 2) );
		CHECK( (vv[0] == 2 && vv[1] == 3) );

		Math::Vector3i v2(-2);
		CHECK( -v == v2 );

		v = 2;
		Math::Vector3i v3(4,5,6);
		CHECK( (v += vv) == v3);

		v = 2;
		Math::Vector3i v4(0,-1, -2);
		CHECK( (v -= vv) == v4);

		v = 2;
		Math::Vector3i v5(4,6,8);
		CHECK( (v *= vv) == v5);

		v = 2;
		Math::Vector3i v6(1,0,0); //integer division
		CHECK( (v /= vv) == v6);

		v = 2;
		Math::Vector3i v7(3,3,3);
		CHECK( (v += 1) == v7 ); //freaking hell
	}
}

TEST_CASE("Vector3 methods work correctly with float", "[math][vector][vector-3]") {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Vector3f v(2.0);
	Math::Vector3f vv(2.0,3.5,4.5);
	Math::Vector3f vvv(v);

	REQUIRE( v == v );
	REQUIRE( v != vv );
	REQUIRE( vv == vv );
	REQUIRE( v == vvv );

	SECTION("methods outside of the Vector3 struct using float") {
		CHECK( Math::toString(v) == "(2.000000, 2.000000, 2.000000)" );
		CHECK( Math::toString(vv) == "(2.000000, 3.500000, 4.500000)" );

		REQUIRE( Math::Length(v) == Approx(std::sqrt(12.0)) );
		REQUIRE( Math::LengthSq(v) == Approx(12.0) );
		REQUIRE( Math::Length(vv) == Approx(std::sqrt(2.0*2.0 + 3.5*3.5 + 4.5*4.5)) );
		REQUIRE( Math::LengthSq(vv) == Approx(2.0*2.0 + 3.5*3.5 + 4.5*4.5) );

		CHECK( Math::Dot(v,v) == Approx(12.0) );
		CHECK( Math::Dot(v,vv) == Approx(20.0) );

		CHECK( Math::Cross(v,v) == 0.0 );
		Math::Vector3f v2(2.0,-5.0, 3.0);
		CHECK( Math::Cross(v,vv) == v2 );

		float len = Math::Length(v);
		Math::Vector3f v4(2.0/len,2.0/len, 2.0/len);
		CHECK( Math::Normalize(v) == v4 );

		len = Math::Length(vv);
		Math::Vector3f v5(2.0/len,3.5/len, 4.5/len);
		CHECK( Math::Normalize(vv) == v5 );
	}

	SECTION("operators inside of the Vector3 struct using float") {
		CHECK( (v[0] == Approx(2.0) && v[1] == Approx(2.0)) );
		CHECK( (vv[0] == Approx(2.0) && vv[1] == Approx(3.5)) );

		Math::Vector3f v2(-2.0);
		CHECK( -v == v2 );

		v = 2.0;
		Math::Vector3f v3(4.0,5.5,6.5);
		CHECK( (v += vv) == v3);

		v = 2.0;
		Math::Vector3f v4(0.0,-1.5,-2.5);
		CHECK( (v -= vv) == v4);

		v = 2.0;
		Math::Vector3f v5(4.0,7.0,9.0);
		CHECK( (v *= vv) == v5);

		v = 2.0;
		Math::Vector3f v6(1.0,2.0/3.5,2.0/4.5);
		CHECK( (v /= vv) == v6);

		v = 2.0;
		Math::Vector3f v7(3.0);
		CHECK( (v + 1.0f) == v7 ); //freaking hell
	}
}

//************************* Matrices *************************
TEST_CASE( "Matrix3 methods work correctly with int", "[math][matrix][matrix-2]" ) {
	using namespace Core;

	//Test Constructor equivalence and equivalence operator
	Math::Matrix3i m(2);
	Math::Matrix3i mm(2,3,4);
	Math::Matrix3i mmm(m);

	REQUIRE( m == m );
	REQUIRE( m != mm );
	REQUIRE( mm == mm );
	REQUIRE( m == mmm );

	SECTION("methods outside of the Matrix3 struct using int") {

	}

	SECTION("operators inside of the Matrix3 struct using int") {
		REQUIRE( m[0] == m[0] );
		CHECK( (m[0] == Math::Vector3i(2) && m[1] == Math::Vector3i(2) && m[2] == Math::Vector3i(2)) );
		CHECK( (mm[0] == Math::Vector3i(2) && mm[1] == Math::Vector3i(3) && mm[2] == Math::Vector3i(4)) );
		CHECK( (mm[0][0] == 2 && mm[1][0] == 3 && mm[2][0] == 4) );
	}
}
#endif
