#include "../Include/Boost.h"

#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>

using namespace boost::filesystem;
using namespace std;

/**
 * Reads in a path to return a vector containing contents of directory.
 *
 * @param p - path to display contents of
 * @return direct - vector of strings containing contents of p
 */
vector<string> ListDir(path p) {
	vector<string> direct;

	if (is_directory(p)) {
		for (auto && x : directory_iterator(p)) {
			direct.push_back(x.path().filename().string());
		}
	} else if (is_regular_file(p)) {
		cout << p << " is a file.";
	} else {
		cout << p << " Hey, that does not exist!";
	}

	for (size_t i = 0; i < direct.size(); i++) {
		cout << direct[i] << '\n';
	}

	return direct;
}





