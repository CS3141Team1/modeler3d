#include "../Include/FileIO.h"

#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <vector>
#include <iostream>
#include <sstream>

void FileIO::SaveObj(boost::filesystem::path p){

}

void FileIO::SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices, std::vector<std::vector<int>> faceElements){

}

void FileIO::SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices,
		std::vector<std::vector<double>> textureVectices, std::vector<std::vector<double>> normalVectices, std::vector<std::vector<int>> faceElements){

}
/*
 *
void FileIO::SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices,
		std::vector<std::vector<double>> newTextureVectices, std::vector<std::vector<double>> newNormalVectices,
		std::vector<std::vector<int>> newFaceElements){

}
*/

void FileIO::LoadObj(boost::filesystem::path p)
{
		boost::filesystem::ifstream file(p);
		std::string fileLine;
		while(std::getline(file, fileLine))
		{
			//std::cout<<fileLine<<"\n";

			if(fileLine.size() > 2){
				if(fileLine.at(0) == 'v' && fileLine.at(1) == ' '){
					double x, y, z;
					std::stringstream ss(fileLine);
					char temp;
					ss >> temp;
					ss >> x;
					ss >> y;
					ss >> z;

					std::vector<double> geometricVector;
					geometricVector.push_back(x);
					geometricVector.push_back(y);
					geometricVector.push_back(z);

					geometricVertices.push_back(geometricVector);
				}

				if(fileLine.at(0) == 'v' && fileLine.at(1) == 't'){
					double x, y;
					std::stringstream ss(fileLine);
					char temp;
					char temp2;
					ss >> temp;
					ss >> temp2;
					ss >> x;
					ss >> y;

					std::vector<double> textureVector;

					textureVector.push_back(x);
					textureVector.push_back(y);

					textureVertices.push_back(textureVector);
				}

			if(fileLine.at(0) == 'v' && fileLine.at(1) == 'n'){
				double x, y, z;
				std::stringstream ss(fileLine);
				char temp;
				char temp2;
				ss >> temp;
				ss >> temp2;
				ss >> x;
				ss >> y;
				ss >> z;

				std::vector<double> normalVector;

				normalVector.push_back(x);
				normalVector.push_back(y);
				normalVector.push_back(z);

				normalVertices.push_back(normalVector);
			}

			if(fileLine.at(0) == 'f' && fileLine.at(1) == ' '){
				int v1, v2, v3;
				std::stringstream ss(fileLine);
				char temp;
				ss >> temp;
				std::vector<int> verticeVector1;
				std::vector<std::vector<int>> faceVector;

				ss >> v1;
				verticeVector1.push_back(v1);

				if(ss.peek() == '/')
					ss >> temp;

				if(ss.peek() != '/' || ss.peek() != ' '){
					ss >> v2;
					verticeVector1.push_back(v2);
				}
				else
					verticeVector1.push_back(0);

				if(ss.peek() == '/')
					ss >> temp;

				if(ss.peek() != '/' || ss.peek() != ' '){
					ss >> v3;
					verticeVector1.push_back(v3);
				}
				else
					verticeVector1.push_back(0);

				faceVector.push_back(verticeVector1);
				std::vector<int> verticeVector2;

				ss >> v1;
				verticeVector2.push_back(v1);
				if(ss.peek() == '/')
					ss >> temp;

				if(ss.peek() != '/' || ss.peek() != ' '){
					ss >> v2;
					verticeVector2.push_back(v2);
				}
				else
					verticeVector2.push_back(0);

				if(ss.peek() == '/')
					ss >> temp;

				if(ss.peek() != '/' || ss.peek() != ' '){
					ss >> v3;
					verticeVector2.push_back(v3);
				}
				else
					verticeVector2.push_back(0);

				faceVector.push_back(verticeVector2);
				std::vector<int> verticeVector3;

				ss >> v1;
				verticeVector3.push_back(v1);
				if(ss.peek() == '/')
					ss >> temp;

				if(ss.peek() != '/' || ss.peek() != ' '){
					ss >> v2;
					verticeVector3.push_back(v2);
				}
				else
					verticeVector3.push_back(0);

				if(ss.peek() == '/')
					ss >> temp;

				if(ss.peek() != '/' || ss.peek() != ' '){
					ss >> v3;
					verticeVector3.push_back(v3);
				}
				else
					verticeVector3.push_back(0);

				faceVector.push_back(verticeVector3);
				faceElements.push_back(faceVector);
			}
			}
		}

}

std::vector<std::vector<double>> FileIO::getGeometricVertices(){
	return geometricVertices;
}
void FileIO::setGeometricVertices(std::vector<std::vector<double>> newGeometricVertices){

}

std::vector<std::vector<double>> FileIO::getTextureVertices(){
	return textureVertices;
}
void FileIO::setTextureVertices(std::vector<std::vector<double>> newTextureVertices){

}
std::vector<std::vector<double>> FileIO::getNormalVertices(){
	return normalVertices;
}
void FileIO::setNoramlVertices(std::vector<std::vector<double>> newNoramlVertices){

}

std::vector<std::vector<std::vector<int>>> FileIO::getFaceElements(){
	return faceElements;
}
void FileIO::setFaceElements(std::vector<std::vector<std::vector<int>>> newFaceElements){

}

void FileIO::Test(){
	std::cout << "test";
}
