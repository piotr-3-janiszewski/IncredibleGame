#include <events/links/IntroductionEvent.hpp>
#include <IO/IOManager.hpp>

const char* IntroductionEvent::get_name() {
	return "Introduction";
}

bool IntroductionEvent::run(GameState state, EventChain* chain) {
	IOManager& io = IOManager::access_singleton();

	io.format_and_print("You are the Grib-man. But alas, recently, you have met a /paint{italic}<millionaire>., and understood in an instance that it's not the shrooms that matter the most!\n");
	io.wait();
	io.format_and_print("It. Is./paint{bright-yellow}</widen< MONEY>.>..\n");
	io.format_and_print("Now the only thing you wish for in this world is the glittering of gold — the blinding sparkle which outshines any shroom you've ever seen. You thirst for the power it gives — for the pleasure that gives the conviction that you can bend the wills of others with the coins in your pocket. Some say avarice is a bane of humanity, but for you it is a burning fire that pushes you forward to greatness!\n");
	io.wait();
	io.format_and_print("Unfortunately, now you have almost nothing. Only a threadbare basket filled to the brim with shrooms of dubious edibility faithfully keeps by your side. You can't remember the last time you have actually owned anything else. The fruits of the forest used to be the only thing you needed.\n");
	io.wait();
	io.format_and_print("You stand in the forest perplexed. You don't have the faintest idea where to look for money. You start strolling around aimlessly.\n");
	io.wait();

	io.format_and_print("/add_speaker{goat}{{normal}{light}{left}{left}}{set}{{/paint{grey}}}<the Gambling Goat>.");
	io.format_and_print("/add_speaker{me}{{normal}{light}{right}{right}}{set}{}<Me>.");

	io.format_and_print("/say{goat}<¡Hola muchacho!><¿Cómo estas?><¿Querías jugar un poquito?>.");
	io.format_and_print("You see a goat with long /paint{black}{bg-white}<black horns>., and /paint{red}<red eyes>. It reeks god-awful — probably just like any other billy goat. The rancid stench makes your eyes water a bit.\n");
	io.wait();
	io.format_and_print("/say{me}<Why in the name of Fungi does this /name{goat}<goat>. speak?><And why does it sound like latin?>.");
	io.format_and_print("/add_speaker{satan}{{normal}{light}{left}{left}{0}{{/paint{bg-black}{red}}}{{/paint{bg-black}{red}}}}{set}{{/paint{bg-black}{red}}}<Satan>.");
	io.format_and_print("/say{goat}<I was trying to add a bit of mistery and biblicall atmosphere to my parlance.><As a child of /name{satan}<Satan>. it would be unbecoming of me to speak like some svoloch,><without /paint{italic}<intrigue>. and /rainbow<mysticism>.!>.");
	io.wait();
	io.format_and_print("You wait a bit, unsure of what to do in the face of an unholy beast talking and claiming to be the child of the Satan himself!\n");
	io.wait();
	io.format_and_print("/say{goat}<What are you waiting for you moron? You are going to play with me or not?>.");
	io.format_and_print("You just notice that the /name{goat}<spawn>. of /name{satan}<Lucifer>. sits behind a trunk, on top of wich lies a deck of cards. A few small anmials blending with the backround sit around the makeshift table and hold a hand of cards.\n");
	io.wait();
	io.format_and_print("/choice{q}<Join the /name{goat}<Goat>. and his friends!>{w}</widen</negative<PANIC AND SCREAM>.>.>.");
	char choice = io.read_repeat("qw");

	if (choice == 'w') {
		io.format_and_print("You /paint{red}<panic>. so hard, that get an /negative<aneursym>. and die.");
		io.wait();
		io.format_and_print("Good job bucko. Better luck (/paint{italic}<skill>.) next time!");
		io.wait();
	}

	return go_to_next(state, chain);
}
