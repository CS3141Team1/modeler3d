#pragma once

#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>

/**
 * Class header file for loading and saving for 3d modeler
 *
 * @author Ryan Hamilton
 */
class FileIO{
	private:
		std::vector<std::vector<double>>* mGeometricVertices;
		std::vector<std::vector<double>>* mTextureCoordinates;
		std::vector<std::vector<double>>* mNormalVertices;
		std::vector<std::vector<std::vector<int>>>* mFaceElements;
		
		//parse string to retrieve the values for the geometric vertices, texture coordinates, normal vertices, and the face elements of the object.
		void mParseGeometricVertex( std::string str, std::vector< std::vector< double > > &refGeometricVertices );
		void mParseTextureCoordinates( std::string str, std::vector< std::vector< double > > &refTextureCoordinates );
		void mParseNormalVertex( std::string str, std::vector< std::vector< double > > &refNormalVertices );
		void mParseFaceElements( std::string str, std::vector< std::vector< std::vector< int > > > &refFaceElements );

		
	public:
	
		//Save methods for .obj files
		void SaveObj(std::string filename);

		
		//load method for .onj files
		void LoadObj( boost::filesystem::path p );
		void LoadObj2( boost::filesystem::path p, std::vector< std::vector< double > > &refGeometricVertices,
				std::vector< std::vector< double > > &refTextureCoordinates, std::vector< std::vector<double > > &refNormalVertices,
				std::vector< std::vector< std::vector< int > > > &refFaceElements );
};
