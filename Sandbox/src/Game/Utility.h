#pragma once

#include <string>
#include <vector>
#include <sstream>

inline std::vector<std::string> DelimitedStringToVector(const std::string& str)
{
	std::vector<std::string> result;

	std::stringstream ss(str);
	while (ss.good())
	{
		std::string substr;
		std::getline(ss, substr, ',');

		if (!substr.empty())
			result.push_back(substr);
	}

	return result;
}