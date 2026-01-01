#include <events/EventChain.hpp>
#include <events/GameState.hpp>
#include <IO/IOManager.hpp>

#include <iostream>

void EventChain::set_chain(std::initializer_list<Event*> events) {
	set_chain(*(events.begin()));
	Event* const * beginning = events.begin();
	Event* const * next = events.begin() + 1;

	while (next < events.end()) {
		(*beginning)->set_next(*next);

		beginning++;
		next++;
	}
}

void EventChain::set_chain(Event* events) {
	this->events = events;
}

void EventChain::begin() {
	if (events == nullptr) {
		std::cerr << "EventChain Error: No events set!" << std::endl;
		return;
	}

	bool run = true;
	while(run) {
		
		GameState state;
		events->run(state, this);

		IOManager& io = IOManager::access_singleton();
		io.format_and_print(state.str());
		io.format_and_print("/choice<Would you like to play again?>{y}</affirmative<Yes!>.>{n}</negative<No...>.>.");

		char choice;
		choice = io.read_repeat("yn");

		if (choice == 'n')
			run = false;
	}
}

EventChain::~EventChain() {
	delete events;
}
