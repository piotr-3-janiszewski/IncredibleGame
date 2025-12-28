#pragma once

#include <string>

struct GameState {
	int score = 0;
	bool victory = false;

	std::string str();
};
