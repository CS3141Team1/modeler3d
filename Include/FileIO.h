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
		std::vector<std::vector<double>> mGeometricVertices;
		std::vector<std::vector<double>> mTextureVertices;
		std::vector<std::vector<double>> mNormalVertices;
		std::vector<std::vector<std::vector<int>>> mFaceElements;
		
	public:
	
		//Save methods for .obj files
		void SaveObj(boost::filesystem::path p);
		void SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices, std::vector<std::vector<int>> newFaceElements);
		void SaveObj(boost::filesystem::path p, std::vector<std::vector<double>> newGeometricVertices,
				std::vector<std::vector<double>> newTextureVectices, std::vector<std::vector<double>> newNormalVectices,
				std::vector<std::vector<int>> newFaceElements);
		
		//load method for .onj files
		void LoadObj(boost::filesystem::path p);
		
		//Get and Set methods for geometric vertices
		std::vector<std::vector<double>> getGeometricVertices();
		void SetGeometricVertices(std::vector<std::vector<double>> newGeometricVertices);
		
		//Get and Set methods for texture vertices
		std::vector<std::vector<double>> GetTextureVertices();
		void SetTextureVertices(std::vector<std::vector<double>> newTextureVertices);
		
		//Get and Set methods for normal vertices
		std::vector<std::vector<double>> GetNormalVertices();
		void SetNoramlVertices(std::vector<std::vector<double>> newNoramlVertices);
		
		//Get and Set methods for Face elements
		std::vector<std::vector<std::vector<int>>> GetFaceElements();
		void SetFaceElements(std::vector<std::vector<std::vector<int>>> newFaceElements);
};
