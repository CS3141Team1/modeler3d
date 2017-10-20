#include "../Include/FileIO.h"

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
void FileIO::LoadObj(boost::filesystem::path p){
		boost::filesystem::ifstream file(p);
		std::string fileLine;
		while(std::getline(file, fileLine)){

			std::cout<<fileLine<<"\n";
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
				double x, y, z;
				std::stringstream ss(fileLine);
				char temp;
				char temp2;
				ss >> temp;
				ss >> temp2;
				ss >> x;
				ss >> y;
				ss >> z;

				std::vector<double> textureVector;

				textureVector.push_back(x);
				textureVector.push_back(y);
				textureVector.push_back(z);

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
			/*
			if(fileLine.at(0) == 'v' && fileLine.at(1) == 'n'){
							int v1, v2, v3;
							std::stringstream ss(fileLine);
							char temp;
							char temp2;
							ss >> temp;
							ss >> temp2;
							ss >> v1;
							ss >> v2;
							ss >> v3;

							std::vector<int> faceVector;

							faceVector.push_back(v1);
							faceVector.push_back(v2);
							faceVector.push_back(v3);

							faceElements.push_back(faceVector);
			}
			*/
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
std::vector<std::vector<int>> FileIO::getFaceElements(){
	return faceElements;
}
void FileIO::setFaceElements(std::vector<std::vector<int>> newFaceElements){

}

void FileIO::Test(){
	std::cout << "test";
}
