#pragma once

#include <events/Event.hpp>

class IntroductionEvent :public Event {
public:
	bool run(GameState state, EventChain* chain);
	const char* get_name() override;
};
