#include <events/EventChain.hpp>
#include <IO/IOManager.hpp>

#include <iostream>

void EventChain::set_chain(Event* events) {
	this->events = events;
}

void EventChain::begin() {
	if (events == nullptr) {
		std::cerr << "EventChain Error: No events set!" << std::endl;
		return;
	}

	while(events->run(GameState(), this));
}

bool EventChain::end(GameState state) {
	IOManager& io = IOManager::access_singleton();
	io.format_and_print(state.str());
	io.format_and_print("/choice<Would you like to play again?>{y}</affirmative<Yes!>.>{n}</negative<No...>.>");

	char choice;
	choice = io.read_repeat("yn");

	if (choice == 'y')
		return true;

	return false;
}
