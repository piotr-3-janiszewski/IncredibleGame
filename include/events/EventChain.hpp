#pragma once

#include <events/Event.hpp>
#include <events/GameState.hpp>

class Event;

class EventChain {
private:
	Event* events = nullptr;
public:
	void set_chain(Event* events);
	void begin();
	bool end(GameState state);
};
