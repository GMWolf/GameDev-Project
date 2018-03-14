#include "stdafx.h"
#include "File.h"
#include <fstream>

bool File::read(std::string file, std::string & string)
{
	std::ifstream is(file);
	if (!is) {
		return false;
	}

	string.assign((std::istreambuf_iterator<char>(is)), (std::istreambuf_iterator<char>()));
	is.close();
	return true;
}