#pragma once

#include <events/GameState.hpp>
#include <events/EventChain.hpp>

class EventChain;

class Event {
private:
	Event* next_event = nullptr;
public:
	void set_next(Event* next_event);
	bool go_to_next(GameState state, EventChain* chain);

	virtual bool run(GameState state, EventChain* chain) = 0;
	virtual const char* get_name() = 0;

	virtual ~Event();
	Event();
	Event(const Event&) = delete;
	Event& operator=(const Event&) = delete;
};
