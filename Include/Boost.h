#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <vector>
#include <iostream>

using namespace boost::filesystem;
using namespace std;

vector<string> ListDir(path p);
vector<string> ListVert(string inFile);
vector<string> ListTexture(string inFile);
vector<string> ListNorm(string inFile);
