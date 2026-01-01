#pragma once

#include <vector>
#include <string>

class Hand : public std::vector<std::string>{
public:
	std::string str();
};
