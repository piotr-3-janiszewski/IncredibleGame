#pragma once

#include <events/Event.hpp>
#include <events/GameState.hpp>

#include <initializer_list>

class Event;

class EventChain {
private:
	Event* events = nullptr;
public:
	void set_chain(Event* events);
	void set_chain(std::initializer_list<Event*> events);
	void begin();
	~EventChain();
};
