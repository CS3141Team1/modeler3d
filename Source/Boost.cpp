#include "../Include/Boost.h"
#include "Types.h"

#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>

using namespace boost::filesystem;
using namespace std;

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

	for (uint i = 0; i < direct.size(); i++) {
		cout << direct[i] << '\n';
	}

	return direct;
}





