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

inline std::string Substring(const std::string& str,  const std::string& delimiter)
{
	std::string s = str;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());
	}

	return s;
}

inline std::string& LeftTrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

inline std::string& RightTrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

inline std::string& Trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
	return LeftTrim(RightTrim(str, chars), chars);
}