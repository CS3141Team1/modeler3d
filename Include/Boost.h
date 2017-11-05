#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <vector>
#include <iostream>

using namespace boost::filesystem;
using namespace std;

/**
 * Class header file for reading directories using boost library.
 *
 * @author Chris Blatt
 */

vector<string> ListDir(path p);
