#include "../Include/FileIO.h"

#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <vector>
#include <iostream>
#include <sstream>

/**
 * Class for loading and saving for 3d modeler
 *
 * @author Ryan Hamilton
 */


/**
 * Save 3d model as a .obj
 *
 * @param p - A path
 */
void FileIO::SaveObj(boost::filesystem::path p)
{

}

/**
 * Save 3d model as a .obj
 *
 * @param p - A path
 *        newmGeometricVertices - A vector<vector<double>>
 *        newFaceElements - A vector<vector<vector<int>>>
 */
void FileIO::SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices, std::vector<std::vector<std::vector<int>>> newFaceElements)
{

}

/**
 * Save 3d model as a .obj
 *
 * @param p - A path
 *        newmGeometricVertices - A vector<vector<double>>
 *		  newTextureVectices - A vector<vector<double>>
 *        newNormalVectices - A vector<vector<double>>
 *        newFaceElements - A vector<vector<vector<int>>>
 */
void FileIO::SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newmGeometricVertices,
		std::vector<std::vector<double>> newTextureVectices, std::vector<std::vector<double>> newNormalVectices, std::vector<std::vector<int>> mFaceElements)
		{

}
/*
 *
void FileIO::SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newmGeometricVertices,
		std::vector<std::vector<double>> newTextureVectices, std::vector<std::vector<double>> newNormalVectices,
		std::vector<std::vector<int>> newmFaceElements){

}
*/

/**
 * Loads a .obj file and parses the file for the geometric vertices, texture coordinates, normal vertices, and face elements from the .obj file
 *
 * @param p - path of .obj file
 */
void FileIO::LoadObj(boost::filesystem::path p)
{
	boost::filesystem::ifstream File(p);
	std::string FileLine;
	
	//loops through entire .obj file
	while(std::getline(File, FileLine))
	{
		std::cout<<FileLine<<"\n";

		if(FileLine.size() > 2){
			
			//checks for Geometric vertex coordinates
			if(FileLine.at(0) == 'v' && FileLine.at(1) == ' ')
			{
				double X, Y, Z;
				std::stringstream S(FileLine);
				char Temp;
				S >> Temp;
				S >> X;
				S >> Y;
				S >> Z;

				std::vector<double> GeometricVector;
				GeometricVector.push_back(X);
				GeometricVector.push_back(Y);
				GeometricVector.push_back(Z);

				mGeometricVertices.push_back(GeometricVector);
			}

			//checks for texture coordinates
			if(FileLine.at(0) == 'v' && FileLine.at(1) == 't')
			{
				double X, Y;
				std::stringstream S(FileLine);
				char Temp;
				char Temp2;
				S >> Temp;
				S >> Temp2;
				S >> X;
				S >> Y;

				std::vector<double> TextureVector;

				TextureVector.push_back(X);
				TextureVector.push_back(Y);

				mTextureVertices.push_back(TextureVector);
			}

			//checks for normal vertex coordinates
			if(FileLine.at(0) == 'v' && FileLine.at(1) == 'n')
			{
				double X, Y, Z;
				std::stringstream S(FileLine);
				char Temp;
				char Temp2;
				S >> Temp;
				S >> Temp2;
				S >> X;
				S >> Y;
				S >> Z;

				std::vector<double> NormalVector;

				NormalVector.push_back(X);
				NormalVector.push_back(Y);
				NormalVector.push_back(Z);

				mNormalVertices.push_back(NormalVector);
			}

			//checks for face elements
			if(FileLine.at(0) == 'f' && FileLine.at(1) == ' ')
			{
				int V1, V2, V3;
				std::stringstream S(FileLine);
				char Temp;
				S >> Temp;
				std::vector<int> VerticeVector1;
				std::vector<std::vector<int>> FaceVector;
				
				//parses through first set of vertices
				S >> V1;
				VerticeVector1.push_back(V1);

				if(S.peek() == '/')
					S >> Temp;

				if(S.peek() != '/' || S.peek() != ' ')
				{
					S >> V2;
					VerticeVector1.push_back(V2);
				}
				else
					VerticeVector1.push_back(0);

				if(S.peek() == '/')
					S >> Temp;

				if(S.peek() != '/' || S.peek() != ' ')
				{
					S >> V3;
					VerticeVector1.push_back(V3);
				}
				else
					VerticeVector1.push_back(0);

				FaceVector.push_back(VerticeVector1);
				std::vector<int> VerticeVector2;

				// parses through second set of vertices
				S >> V1;
				VerticeVector2.push_back(V1);
				
				if(S.peek() == '/')
					S >> Temp;

				if(S.peek() != '/' || S.peek() != ' ')
				{
					S >> V2;
					VerticeVector2.push_back(V2);
				}
				else
					VerticeVector2.push_back(0);

				if(S.peek() == '/')
					S >> Temp;

				if(S.peek() != '/' || S.peek() != ' ')
				{
					S >> V3;
					VerticeVector2.push_back(V3);
				}
				else
					VerticeVector2.push_back(0);

				FaceVector.push_back(VerticeVector2);
				std::vector<int> VerticeVector3;

				//parses through the third set of vertices
				S >> V1;
				VerticeVector3.push_back(V1);
					
				if(S.peek() == '/')
					S >> Temp;

				if(S.peek() != '/' || S.peek() != ' ')
				{
					S >> V2;
					VerticeVector3.push_back(V2);
				}
				else
					VerticeVector3.push_back(0);
	
				if(S.peek() == '/')
					S >> Temp;
	
				if(S.peek() != '/' || S.peek() != ' ')
				{
					S >> V3;
					VerticeVector3.push_back(V3);
				}
				else
					VerticeVector3.push_back(0);

				FaceVector.push_back(VerticeVector3);
				mmFaceElements.push_back(FaceVector);
			}
		}
	}
}

/**
 * Returns the geometric vertices of a .obj file
 *
 * @return mGeometricVertices - A vector<vector<double>>
 */
std::vector<std::vector<double>> FileIO::GetGeometricVertices()
{
	return mGeometricVertices;
}

/**
 * Sets mGeometricVertices to new values in order to be saved
 *
 * @param newGeometricVertices - A vector<vector<double>>
 */
void FileIO::SetGeometricVertices(std::vector<std::vector<double>> FileIO::newGeometricVertices)
{

}

/**
 * Returns the texture vertices of a .obj file
 *
 * @return mTextureVertices - A vector<vector<double>>
 */
std::vector<std::vector<double>> FileIO::GetTextureVertices()
{
	return mTextureVertices;
}

/**
 * Sets mTextureVertices to new values in order to be saved
 *
 * @param newTextureVertices - A vector<vector<double>>
 */
void FileIO::SetTextureVertices(std::vector<std::vector<double>> newTextureVertices)
{

}

/**
 * Returns the normal vertices of a .obj file
 *
 * @return mNormalVertices - A vector<vector<double>>
 */
std::vector<std::vector<double>> FileIO::GetNormalVertices()
{
	return mNormalVertices;
}

/**
 * Sets mNormalVertices to new values in order to be saved
 *
 * @param newNormalVertices - A vector<vector<double>>
 */
void FileIO::SetNoramlVertices(std::vector<std::vector<double>> newNoramlVertices)
{

}
/**
 * Returns the face elements of a .obj file
 *
 * @return mFaceElements - A vector<vector<vector<int>>>
 */
std::vector<std::vector<std::vector<int>>> FileIO::GetFaceElements()
{
	return mFaceElements;
}

/**
 * Sets mFaceElements to new values in order to be saved
 *
 * @param newFaceElements - A vector<vector<vector<int>>>
 */
void FileIO::SetFaceElements(std::vector<std::vector<std::vector<int>>> newFaceElements)
{

}

