#include <iostream>
#include <IO/IOManager.hpp>
#include <events/EventChain.hpp>
#include <events/links/IntroductionEvent.hpp>
#include <events/links/games/Blackjack.hpp>
#include <events/links/scenarios/SadScenario.hpp>

int main() {
	IOManager& io = IOManager::access_singleton(); 
	io.format_and_print("/add_speaker{choice}{{none}{light}{center}{center}}{no}{/paint{bold}}.");
	//io.format_and_print("/box{double}</paint{blink}<WELCOME>.></paint{blink}<TO THE>.></paint{blink}<INCREDIBLE>.></paint{blink}<GAME>.>.");
	io.format_and_print("/box{none}{center}{center}<Welcome to the>.");
	io.format_and_print("/paint{blink}</rainbow</banner{default}{INCREDIBLE GAME}.>.>.\n");
	io.format_and_print("/box{none}{center}{center}</paint{italic}<In order to continue press enter...>.>.");
	io.wait();

	EventChain main_chain;

	main_chain.set_chain({
		new IntroductionEvent(),
		new Blackjack(new SadScenario)
	});

	main_chain.begin();
}
