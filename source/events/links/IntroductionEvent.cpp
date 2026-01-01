#include <events/links/IntroductionEvent.hpp>
#include <IO/IOManager.hpp>

const char* IntroductionEvent::get_name() {
	return "Introduction";
}

GameState IntroductionEvent::run(GameState& state, EventChain* chain) {
	IOManager& io = IOManager::access_singleton();

	io.format_and_print("/paint{bright-yellow}</banner{default}{INTRODUCTION}.>.\n");
	io.format_and_print("/box{none}{center}{center}{0}</paint{italic}<The /paint{bold}<glittering>. /widen<revelation>.>.>.");
	io.wait();
	io.format_and_print("You are the Grib-man. But alas. You have just met the /paint{italic}{bright-yellow}<millionaire GOD>.. You understood in an instance that it is not the shrooms that matter the most!\n");
	io.wait();
	io.format_and_print("It. Is./paint{bright-yellow}</widen< MONEY>.>..\n");
	io.wait();
	io.format_and_print("Now the only thing you wish for, in this world is the /paint{italic}<glittering>. /paint{bright-yellow}<gold>. — the blinding sparkle of which outshines even most glory shrooms. You will do anything for it's beauty and power. Some say avarice is the bane of humanity. For you however, it is a burning fire that pushes you forward to greatness!\n");
	io.wait();
	io.format_and_print("Unfortunately, now you are down-and-out in a remote forest, damp and colorful in a depressing kind-of-way possible only during the fall. Only a trusty threadbare basket filled to the brim with shrooms that most people wouldn't be brave enough to try, faithfully stays by your side. \n");
	io.wait();
	io.format_and_print("You stand in the forest perplexed. You don't have the faintest idea where to look for money... In the end you start strolling around aimlessly, snacking on yummy /rainbow<shrooms>..\n");
	io.wait();

	io.format_and_print("/add_speaker{goat}{{normal}{light}{left}{left}}{set}{{/paint{grey}}}<the Gambling Goat>.");
	io.format_and_print("/add_speaker{me}{{normal}{light}{right}{right}}{set}{}<Me>.");

	io.format_and_print("/say{goat}<¡Hola muchacho!><¿Cómo estas?><¿Querías jugar un poquito?>.");
	io.format_and_print("It says, beckoning to you. You see a goat with long /paint{black}{bg-white}<black horns>., and /paint{red}<red eyes>.. It reeks god-awful — probably just like any other billy goat. The rancid stench makes your eyes water a bit.\n");
	io.wait();
	io.format_and_print("/say{me}<Why in the name of Fungi does this /name{goat}<goat>. speak?><Is that Latin?>.");
	io.wait();
	io.format_and_print("/add_speaker{satan}{{normal}{light}{left}{left}{0}{{/paint{bg-black}{red}}}{{/paint{bg-black}{red}}}}{set}{{/paint{bg-black}{red}}}<Satan>.");
	io.format_and_print("/say{goat}<I was trying to add a bit of mistery and biblical atmosphere to my parlance.><As a child of /name{satan}<Satan>. it would be unbecoming of me to speak like some svoloch,><without /paint{italic}<intrigue>. and /rainbow<mysticism>.!>.");
	io.format_and_print("It says, nodding it's head in an expression of self appreciation.");
	io.wait();
	io.format_and_print("You wait a bit, unsure of what to do in the face of an unholy beast talking and claiming to be the child of the Satan himself!\n");
	io.wait();
	io.format_and_print("/say{goat}<What are you waiting for you moron? You are going to play with me or not?>.");
	io.format_and_print("You suddenly notice that the /name{goat}<spawn>. of /name{satan}<Lucifer>. sits behind a trunk, with a deck of cards lying on top. A few small animals, blending with the backround, sit around the makeshift table and hold hands of cards.\n");
	io.wait();
	io.format_and_print("/choice{q}<Join the /name{goat}<Goat>. and his friends!>{w}</widen</negative<PANIC AND SCREAM>.>.>.");
	char choice = io.read_repeat("qw");

	if (choice == 'w') {
		io.format_and_print("You /paint{red}<panic>. so hard, you get an /negative<aneursym>. and die.\n");
		io.wait();
		io.format_and_print("Good job bucko. Better luck (/paint{italic}<skill>.) next time!\n");
		io.wait();

		state.add_entry("aunerysm", 1, {true, 1000, "/paint{bg-black, white}<Aunerysms: >.", "/negative<", ">."});
		
		return state;
	}

	return go_to_next(state, chain);
}
