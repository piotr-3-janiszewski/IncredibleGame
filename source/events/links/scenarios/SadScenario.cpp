#include <events/links/scenarios/SadScenario.hpp>

std::string SadScenario::with_whom(GameState& state) {
	return "with a sad despicable looser";
}

void SadScenario::introduction(GameState& state) {
	io.format_and_print("/add_speaker{sad}{{double}{light}{left}{left}}{yes}{{/paint{blue}}}{}.");
	io.format_and_print("/say{sad}<This is an introduction to a very /name{sad}<sad>. scenario... :<>.");	
	io.format_and_print("/say{sad}<We'll play some " + std::get<std::string>(state.get_entry("game-name")) + ">.");

}

void SadScenario::rules_inquiry(GameState& state) {
	io.format_and_print("/say{sad}<Are you perhaps /paint{ialic}<au fait>. with the rules of " + std::get<std::string>(state.get_entry("game-name")) + "?>.");
}

void SadScenario::begin_game(GameState& state) {
	io.format_and_print("/say{sad}<Lettuce (sic.) commence!>.");
}

void SadScenario::after_round(GameState& state, int round) {
	std::string result_string;

	if (std::get<bool>(state.get_entry("round won")))
		result_string = "won this time";
	else
		result_string = "were defeated like a loser that you are";

	io.format_and_print("/say{sad}<Wow, you " + result_string + ". How delightful.>.");
}
void SadScenario::won(GameState& state) {
	io.format_and_print("/say{sad}<Końgratulations.>.");
}

void SadScenario::lost(GameState& state) {
	io.format_and_print("/say{sad}<Get rekt kiddo.>.");
}

void SadScenario::small_win(GameState& state) {
	io.format_and_print("/say{sad}<'Tis but a scratch>.");
}

void SadScenario::small_defeat(GameState& state) {
	io.format_and_print("/say{sad}<Git gud>.");
}

void SadScenario::bother(GameState& state) {
	io.format_and_print("/say{sad}<Yes, we are playing /paint{bold}{blink}{red}{bg-black}<.>.>.");
}
