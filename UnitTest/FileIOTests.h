#pragma once

#if DO_UNIT_TESTING==1

#include "FileIO.h"
#include <math.h>
#include "Types.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "../Include/Boost.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

/******************************************
 *
 * Boost Directory Tests
 *
 ******************************************/

/******************************************
 *
 * Boost FilIO Tests
 *
 ******************************************/

    TEST_CASE( "Load .obj file with geometric vertices, texture coordinates, and normal vertices" ) {

        boost::filesystem::path obj( "Assets/cube.obj" );

    	FileIO cubeTest;

    	std::vector< std::vector< double > > positions;
        std::vector< std::vector< double > > textures;
        std::vector< std::vector< double > > normals;
        std::vector< std::vector< std::vector< int > > > faces;

        cubeTest.LoadObj2( obj , positions, textures, normals, faces );


    	//Test Constructor equivalence and equivalence operator
        INFO("Checking the number of vertices in positions");
    	REQUIRE( positions.size( )  == 8 );
    	INFO("Checking the number of coordinates in each position");
    	for( uint i = 0; i < positions.size( ); i++ )
    	{
    		INFO("Vertex " << i );
    		REQUIRE( positions[i].size( ) == 3 );
    	}

    	INFO("Checking the number of coordinate sets in Textures");
    	REQUIRE( textures.size( ) == 4 );
    	INFO("Checking the number of coordinates in each texture");
    	for( uint i = 0; i < textures.size( ); i++ )
    	{
    	    INFO("Texture " << i);
    	 	REQUIRE( textures[i].size( ) == 2 );
    	}

    	INFO("Checking the number of vertices in normals");
    	REQUIRE( normals.size( ) == 6 );
    	INFO("Checking the number of coordinates in each normal");
    	for( uint i = 0; i < normals.size( ); i++ )
    	{
    	    INFO("Normal " << i);
    	    REQUIRE( normals[i].size( ) == 3 );
    	}

    	INFO("Checking the number of faces in faces");
    	REQUIRE( faces.size( ) == 12 );
    	INFO("Checking the number of sets of vertices per face and the number of vertices per set  ");
    	for( uint i = 0; i < faces.size( ); i++ )
    	{
    	    INFO( "Face " << i );
    	    REQUIRE( faces[ i ].size( ) == 3 );
    	    for( uint j = 0; j < faces[ i ].size(); j++ )
    	    {
    	    	INFO( " Vertices set " << j );
    	    	REQUIRE( faces[ i ][ j ].size( ) == 3 );
    	    }
    	}

    	INFO( "Set up testPositions" );
    	std::vector< std::vector< double > > testPositions = { { -0.5,  0.5, -0.5 },
    			                                               { -0.5,  0.5,  0.5 },
															   {  0.5,  0.5,  0.5 },
															   {  0.5,  0.5, -0.5 },
															   { -0.5, -0.5, -0.5 },
															   { -0.5, -0.5,  0.5 },
															   {  0.5, -0.5,  0.5 },
															   {  0.5, -0.5, -0.5 } };

    	INFO("Set up testTextures");
    	std::vector< std::vector< double > > testTextures = { { 0, 1 },
    														  { 0, 0 },
															  { 1, 0 },
															  { 1, 1 } };

    	INFO("Set up testNormals");
    	std::vector< std::vector< double > > testNormals = { { -1,  0,  0 },
    														 {  1,  0,  0 },
															 {  0, -1,  0 },
															 {  0,  1,  0 },
															 {  0,  0, -1 },
															 {  0,  0,  1 } };

    	INFO("Set up testFaces");
    	std::vector< std::vector< std::vector< int > > > testFaces = { { { 6, 4, 1 }, { 2, 3, 1 }, { 1, 2, 1 } },
    																   { { 6, 4, 1 }, { 1, 2, 1 }, { 5, 1, 1 } },
																	   { { 8, 4, 2 }, { 4, 3, 2 }, { 3, 2, 2 } },
																	   { { 8, 4, 2 }, { 3, 2, 2 }, { 7, 1, 2 } },
																	   { { 8, 4, 2 }, { 7, 3, 3 }, { 6, 2, 3 } },
																	   { { 3, 4, 4 }, { 4, 3, 4 }, { 1, 2, 4 } },
																	   { { 3, 4, 4 }, { 1, 2, 4 }, { 2, 1, 4 } },
																	   { { 5, 4, 5 }, { 1, 3, 5 }, { 4, 2, 5 } },
																	   { { 5, 4, 5 }, { 4, 2, 5 }, { 8, 1, 5 } },
																	   { { 7, 4, 6 }, { 3, 3, 6 }, { 2, 2, 6 } },
																	   { { 7, 4, 6 }, { 2, 2, 6 }, { 6, 1, 6 } } };

    	SECTION("Check Geometric Vertices")
    	{
    		for( uint i = 0; i < testPositions.size(); i++ )
    		{
    			for( uint j = 0; j < testPositions[0].size(); j++)
    			{
    				CHECK(testPositions[i][j] == testPositions[i][j]);
    			}
    		}
    	}

    	SECTION("Check texture coordinates")
    	{
    		for( uint i = 0; i < testTextures.size(); i++ )
    		{
    			for( uint j = 0; j < testTextures[0].size(); j++)
    			{
    				CHECK(testTextures[i][j] == testTextures[i][j]);
    			}
    		}
    	}

    	SECTION("Check Nomral Vertices")
    	{
    		for( uint i = 0; i < testNormals.size(); i++ )
    		{
    		    for( uint j = 0; j < testNormals[0].size(); j++)
    		    {
    				CHECK(testNormals[i][j] == testNormals[i][j]);
    		    }
    		}
    	}

    	SECTION("Check Face Elements")
    	{
    		for( uint i = 0; i < testFaces.size(); i++ )
    		{
    			for( uint j = 0; j < testFaces[0].size(); j++)
    			{
    				for( uint k = 0; k < testFaces[0][0].size(); k++)
    				{
    					CHECK(testFaces[i][j][k] == testFaces[i][j][k]);
    				}
    			}
    		}
    	}

    }

    TEST_CASE( "Load .obj file with polygons" ) {

           boost::filesystem::path obj( "Assets/cube2.obj" );

       	FileIO cubeTest;

       	std::vector< std::vector< double > > positions;
           std::vector< std::vector< double > > textures;
           std::vector< std::vector< double > > normals;
           std::vector< std::vector< std::vector< int > > > faces;

           cubeTest.LoadObj2( obj , positions, textures, normals, faces );


       	//Test Constructor equivalence and equivalence operator
           INFO("Checking the number of vertices in positions");
       	REQUIRE( positions.size( )  == 8 );
       	INFO("Checking the number of coordinates in each position");
       	for( uint i = 0; i < positions.size( ); i++ )
       	{
       		INFO("Vertex " << i );
       		REQUIRE( positions[i].size( ) == 3 );
       	}

       	INFO("Checking the number of coordinate sets in Textures");
       	REQUIRE( textures.size( ) == 4 );
       	INFO("Checking the number of coordinates in each texture");
       	for( uint i = 0; i < textures.size( ); i++ )
       	{
       	    INFO("Texture " << i);
       	 	REQUIRE( textures[i].size( ) == 2 );
       	}

       	INFO("Checking the number of vertices in normals");
       	REQUIRE( normals.size( ) == 6 );
       	INFO("Checking the number of coordinates in each normal");
       	for( uint i = 0; i < normals.size( ); i++ )
       	{
       	    INFO("Normal " << i);
       	    REQUIRE( normals[i].size( ) == 3 );
       	}

       	INFO("Checking the number of faces in faces");
       	REQUIRE( faces.size( ) == 12 );
       	INFO("Checking the number of sets of vertices per face and the number of vertices per set  ");
       	for( uint i = 0; i < faces.size( ); i++ )
       	{
       	    INFO( "Face " << i );
       	    REQUIRE( faces[ i ].size( ) == 3 );
       	    for( uint j = 0; j < faces[ i ].size(); j++ )
       	    {
       	    	INFO( " Vertices set " << j );
       	    	REQUIRE( faces[ i ][ j ].size( ) == 3 );
       	    }
       	}

       	INFO( "Set up testPositions" );
       	std::vector< std::vector< double > > testPositions = { { -0.5,  0.5, -0.5 },
       			                                               { -0.5,  0.5,  0.5 },
   															   {  0.5,  0.5,  0.5 },
   															   {  0.5,  0.5, -0.5 },
   															   { -0.5, -0.5, -0.5 },
   															   { -0.5, -0.5,  0.5 },
   															   {  0.5, -0.5,  0.5 },
   															   {  0.5, -0.5, -0.5 } };

       	INFO("Set up testTextures");
       	std::vector< std::vector< double > > testTextures = { { 0, 1 },
       														  { 0, 0 },
   															  { 1, 0 },
   															  { 1, 1 } };

       	INFO("Set up testNormals");
       	std::vector< std::vector< double > > testNormals = { { -1,  0,  0 },
       														 {  1,  0,  0 },
   															 {  0, -1,  0 },
   															 {  0,  1,  0 },
   															 {  0,  0, -1 },
   															 {  0,  0,  1 } };

       	INFO("Set up testFaces");
       	std::vector< std::vector< std::vector< int > > > testFaces = { { { 6, 4, 1 }, { 2, 3, 1 }, { 1, 2, 1 } },
       																   { { 6, 4, 1 }, { 1, 2, 1 }, { 5, 1, 1 } },
   																	   { { 8, 4, 2 }, { 4, 3, 2 }, { 3, 2, 2 } },
   																	   { { 8, 4, 2 }, { 3, 2, 2 }, { 7, 1, 2 } },
   																	   { { 8, 4, 2 }, { 7, 3, 3 }, { 6, 2, 3 } },
   																	   { { 3, 4, 4 }, { 4, 3, 4 }, { 1, 2, 4 } },
   																	   { { 3, 4, 4 }, { 1, 2, 4 }, { 2, 1, 4 } },
   																	   { { 5, 4, 5 }, { 1, 3, 5 }, { 4, 2, 5 } },
   																	   { { 5, 4, 5 }, { 4, 2, 5 }, { 8, 1, 5 } },
   																	   { { 7, 4, 6 }, { 3, 3, 6 }, { 2, 2, 6 } },
   																	   { { 7, 4, 6 }, { 2, 2, 6 }, { 6, 1, 6 } } };



       	SECTION("Check Geometric Vertices")
       	{
       		for( uint i = 0; i < testPositions.size(); i++ )
       		{
       			for( uint j = 0; j < testPositions[0].size(); j++)
       			{
       				CHECK(testPositions[i][j] == testPositions[i][j]);
       			}
       		}
       	}

       	SECTION("Check texture coordinates")
       	{
       		for( uint i = 0; i < testTextures.size(); i++ )
       		{
       			for( uint j = 0; j < testTextures[0].size(); j++)
       			{
       				CHECK(testTextures[i][j] == testTextures[i][j]);
       			}
       		}
       	}

       	SECTION("Check Nomral Vertices")
       	{
       		for( uint i = 0; i < testNormals.size(); i++ )
       		{
       		    for( uint j = 0; j < testNormals[0].size(); j++)
       		    {
       				CHECK(testNormals[i][j] == testNormals[i][j]);
       		    }
       		}
       	}

       	SECTION("Check Face Elements")
       	{
       		for( uint i = 0; i < testFaces.size(); i++ )
       		{
       			for( uint j = 0; j < testFaces[0].size(); j++)
       			{
       				for( uint k = 0; k < testFaces[0][0].size(); k++)
       				{
       					CHECK(testFaces[i][j][k] == testFaces[i][j][k]);
       				}
       			}
       		}
       	}

       }

    TEST_CASE( "Load .obj file with geometric vertices, and normal vertices" ) {

            boost::filesystem::path obj( "Assets/cube3.obj" );

        	FileIO cubeTest;

        	std::vector< std::vector< double > > positions;
            std::vector< std::vector< double > > textures;
            std::vector< std::vector< double > > normals;
            std::vector< std::vector< std::vector< int > > > faces;

            cubeTest.LoadObj2( obj , positions, textures, normals, faces );


        	//Test Constructor equivalence and equivalence operator
            INFO("Checking the number of vertices in positions");
        	REQUIRE( positions.size( )  == 8 );
        	INFO("Checking the number of coordinates in each position");
        	for( uint i = 0; i < positions.size( ); i++ )
        	{
        		INFO("Vertex " << i );
        		REQUIRE( positions[i].size( ) == 3 );
        	}

        	INFO("Checking the number of coordinate sets in Textures");
        	REQUIRE( textures.size( ) == 0 );

        	INFO("Checking the number of vertices in normals");
        	REQUIRE( normals.size( ) == 6 );
        	INFO("Checking the number of coordinates in each normal");
        	for( uint i = 0; i < normals.size( ); i++ )
        	{
        	    INFO("Normal " << i);
        	    REQUIRE( normals[i].size( ) == 3 );
        	}

        	INFO("Checking the number of faces in faces");
        	REQUIRE( faces.size( ) == 12 );
        	INFO("Checking the number of sets of vertices per face and the number of vertices per set  ");
        	for( uint i = 0; i < faces.size( ); i++ )
        	{
        	    INFO( "Face " << i );
        	    REQUIRE( faces[ i ].size( ) == 3 );
        	    for( uint j = 0; j < faces[ i ].size(); j++ )
        	    {
        	    	INFO( " Vertices set " << j );
        	    	REQUIRE( faces[ i ][ j ].size( ) == 3 );
        	    }
        	}

        	INFO( "Set up testPositions" );
        	std::vector< std::vector< double > > testPositions = { { -0.5,  0.5, -0.5 },
        			                                               { -0.5,  0.5,  0.5 },
    															   {  0.5,  0.5,  0.5 },
    															   {  0.5,  0.5, -0.5 },
    															   { -0.5, -0.5, -0.5 },
    															   { -0.5, -0.5,  0.5 },
    															   {  0.5, -0.5,  0.5 },
    															   {  0.5, -0.5, -0.5 } };

        	INFO("Set up testNormals");
        	std::vector< std::vector< double > > testNormals = { { -1,  0,  0 },
        														 {  1,  0,  0 },
    															 {  0, -1,  0 },
    															 {  0,  1,  0 },
    															 {  0,  0, -1 },
    															 {  0,  0,  1 } };

        	INFO("Set up testFaces");
        	std::vector< std::vector< std::vector< int > > > testFaces = { { { 6, 0, 1 }, { 2, 0, 1 }, { 1, 0, 1 } },
        																   { { 6, 0, 1 }, { 1, 0, 1 }, { 5, 0, 1 } },
    																	   { { 8, 0, 2 }, { 4, 0, 2 }, { 3, 0, 2 } },
    																	   { { 8, 0, 2 }, { 3, 0, 2 }, { 7, 0, 2 } },
    																	   { { 8, 0, 2 }, { 7, 0, 3 }, { 6, 0, 3 } },
    																	   { { 3, 0, 4 }, { 4, 0, 4 }, { 1, 0, 4 } },
    																	   { { 3, 0, 4 }, { 1, 0, 4 }, { 2, 0, 4 } },
    																	   { { 5, 0, 5 }, { 1, 0, 5 }, { 4, 0, 5 } },
    																	   { { 5, 0, 5 }, { 4, 0, 5 }, { 8, 0, 5 } },
    																	   { { 7, 0, 6 }, { 3, 0, 6 }, { 2, 0, 6 } },
    																	   { { 7, 0, 6 }, { 2, 0, 6 }, { 6, 0, 6 } } };



        	SECTION("Check Geometric Vertices")
        	{
        		for( uint i = 0; i < testPositions.size(); i++ )
        		{
        			for( uint j = 0; j < testPositions[0].size(); j++)
        			{
        				CHECK(testPositions[i][j] == testPositions[i][j]);
        			}
        		}
        	}

        	SECTION("Check Nomral Vertices")
        	{
        		for( uint i = 0; i < testNormals.size(); i++ )
        		{
        		    for( uint j = 0; j < testNormals[0].size(); j++)
        		    {
        				CHECK(testNormals[i][j] == testNormals[i][j]);
        		    }
        		}
        	}

        	SECTION("Check Face Elements")
        	{
        		for( uint i = 0; i < testFaces.size(); i++ )
        		{
        			for( uint j = 0; j < testFaces[0].size(); j++)
        			{
        				for( uint k = 0; k < testFaces[0][0].size(); k++)
        				{
        					CHECK(testFaces[i][j][k] == testFaces[i][j][k]);
        				}
        			}
        		}
        	}

        }

    TEST_CASE( "Load .obj file with geometric vertices" ) {

            boost::filesystem::path obj( "Assets/cube4.obj" );

        	FileIO cubeTest;

        	std::vector< std::vector< double > > positions;
            std::vector< std::vector< double > > textures;
            std::vector< std::vector< double > > normals;
            std::vector< std::vector< std::vector< int > > > faces;

            cubeTest.LoadObj2( obj , positions, textures, normals, faces );


        	//Test Constructor equivalence and equivalence operator
            INFO("Checking the number of vertices in positions");
        	REQUIRE( positions.size( )  == 8 );
        	INFO("Checking the number of coordinates in each position");
        	for( uint i = 0; i < positions.size( ); i++ )
        	{
        		INFO("Vertex " << i );
        		REQUIRE( positions[i].size( ) == 3 );
        	}

        	INFO("Checking the number of coordinate sets in Textures");
        	REQUIRE( textures.size( ) == 0 );

        	INFO("Checking the number of vertices in normals");
        	REQUIRE( normals.size( ) == 0 );
        	INFO("Checking the number of coordinates in each normal");

        	INFO("Checking the number of faces in faces");
        	REQUIRE( faces.size( ) == 12 );
        	INFO("Checking the number of sets of vertices per face and the number of vertices per set  ");
        	for( uint i = 0; i < faces.size( ); i++ )
        	{
        	    INFO( "Face " << i );
        	    REQUIRE( faces[ i ].size( ) == 3 );
        	    for( uint j = 0; j < faces[ i ].size(); j++ )
        	    {
        	    	INFO( " Vertices set " << j );
        	    	REQUIRE( faces[ i ][ j ].size( ) == 3 );
        	    }
        	}

        	INFO( "Set up testPositions" );
        	std::vector< std::vector< double > > testPositions = { { -0.5,  0.5, -0.5 },
        			                                               { -0.5,  0.5,  0.5 },
    															   {  0.5,  0.5,  0.5 },
    															   {  0.5,  0.5, -0.5 },
    															   { -0.5, -0.5, -0.5 },
    															   { -0.5, -0.5,  0.5 },
    															   {  0.5, -0.5,  0.5 },
    															   {  0.5, -0.5, -0.5 } };

        	INFO("Set up testFaces");
        	std::vector< std::vector< std::vector< int > > > testFaces = { { { 6, 0, 0 }, { 2, 0, 0 }, { 1, 0, 0 } },
        																   { { 6, 0, 0 }, { 1, 0, 0 }, { 5, 0, 0 } },
    																	   { { 8, 0, 0 }, { 4, 0, 0 }, { 3, 0, 0 } },
    																	   { { 8, 0, 0 }, { 3, 0, 0 }, { 7, 0, 0 } },
    																	   { { 8, 0, 0 }, { 7, 0, 0 }, { 6, 0, 0 } },
    																	   { { 3, 0, 0 }, { 4, 0, 0 }, { 1, 0, 0 } },
    																	   { { 3, 0, 0 }, { 1, 0, 0 }, { 2, 0, 0 } },
    																	   { { 5, 0, 0 }, { 1, 0, 0 }, { 4, 0, 0 } },
    																	   { { 5, 0, 0 }, { 4, 0, 0 }, { 8, 0, 0 } },
    																	   { { 7, 0, 0 }, { 3, 0, 0 }, { 2, 0, 0 } },
    																	   { { 7, 0, 0 }, { 2, 0, 0 }, { 6, 0, 0 } } };



        	SECTION("Check Geometric Vertices")
        	{
        		for( uint i = 0; i < testPositions.size(); i++ )
        		{
        			for( uint j = 0; j < testPositions[0].size(); j++)
        			{
        				CHECK(testPositions[i][j] == testPositions[i][j]);
        			}
        		}
        	}

        	SECTION("Check Face Elements")
        	{
        		for( uint i = 0; i < testFaces.size(); i++ )
        		{
        			for( uint j = 0; j < testFaces[0].size(); j++)
        			{
        				for( uint k = 0; k < testFaces[0][0].size(); k++)
        				{
        					CHECK(testFaces[i][j][k] == testFaces[i][j][k]);
        				}
        			}
        		}
        	}

        }

#endif
