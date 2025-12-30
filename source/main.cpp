#include <iostream>
#include <IO/IOManager.hpp>
#include <events/EventChain.hpp>
#include <events/links/IntroductionEvent.hpp>

int main() {
	IOManager& io = IOManager::access_singleton(); 
	io.format_and_print("/add_speaker{choice}{{none}{left}{center}}{no}{/paint{bold}}.");
	io.format_and_print("/box{double}</paint{blink}<WELCOME>.></paint{blink}<TO THE>.></paint{blink}<INCREDIBLE>.></paint{blink}<GAME>.>.");

	EventChain main_chain;
	main_chain.set_chain(new IntroductionEvent());

	main_chain.begin();
}
