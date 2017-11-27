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
			if (is_directory(x)) {
				std::string dir = x.path().filename().string();
				direct.push_back(dir.append("/"));
			} else {
				direct.push_back(x.path().filename().string());
			}
		}
	} else if (is_regular_file(p)) {
		direct.push_back("That path is a file.");
		//cout << p << " is a file.";
	} else {
		direct.push_back("That path does not exist!");
		//cout << p << " does not exist!";
	}

	/*for (uint i = 0; i < direct.size(); i++) {
		cout << direct[i] << '\n';
	}*/

	return direct;
}





