#pragma once

#include <events/Event.hpp>

class IntroductionEvent :public Event {
public:
	GameState run(GameState& state, EventChain* chain) override;
	const char* get_name() override;
};
