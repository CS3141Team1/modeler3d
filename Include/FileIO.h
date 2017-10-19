#pragma once

#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>

class FileIO{
	private:

		std::vector<std::vector<double>> geometricVertices;
		std::vector<std::vector<double>> textureVertices;
		std::vector<std::vector<double>> normalVertices;
		std::vector<std::vector<int>> faceElements;
	public:
		void SaveObj(boost::filesystem::path p);
		void SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices, std::vector<std::vector<int>> newFaceElements);
		void SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices,
				std::vector<std::vector<double>> newTextureVectices, std::vector<std::vector<double>> newNormalVectices,
				std::vector<std::vector<int>> newFaceElements);
		void LoadObj(boost::filesystem::path p);
		std::vector<std::vector<double>> getGeometricVertices();
		void setGeometricVertices(std::vector<std::vector<double>> newGeometricVertices);
		std::vector<std::vector<double>> getTextureVertices();
		void setTextureVertices(std::vector<std::vector<double>> newTextureVertices);
		std::vector<std::vector<double>> getNoramlVertices();
		void setNoramlVertices(std::vector<std::vector<double>> newNoramlVertices);
		std::vector<std::vector<int>> getFaceElements();
		void setFaceElements(std::vector<std::vector<int>> newFaceElements);
		void Test();
};
