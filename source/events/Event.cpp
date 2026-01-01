#include <events/Event.hpp>

void Event::set_next(Event* next_event) {
	if (this->next_event != nullptr)
		delete next_event;

	this->next_event = next_event;
}

GameState Event::go_to_next(GameState& state, EventChain* chain) {
	if (next_event == nullptr) {
		state.set_entry("victory", true);
		return state;
	}

	return next_event->run(state, chain);
}

Event::Event() {}

Event::~Event() {
	delete next_event;
}
