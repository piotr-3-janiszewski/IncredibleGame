#include <events/links/Game.hpp>
#include <IO/IOManager.hpp>

#include <regex>

GameState Game::run(GameState& state, EventChain* chain) {
	io.format_and_print("/add_speaker{game master}{{none}{light}{center}{center}{0}{}{{/paint{italic}}}}{true}{}{***}.");
	io.format_and_print(std::string("/paint{red}</banner{default}{") + get_name() + "}.>.");
	io.format_and_print("/say{game master}<" + scenario->with_whom(state) + ">.");

	if (!state.contains("game-name")) {
		state.add_entry("game-name", get_name(), {false});
	}

	state.set_entry("game-name", get_name());

	scenario->introduction(state);
	io.wait();
	scenario->rules_inquiry(state);
	io.wait();

	io.format_and_print("/choice<Would you like to read the rules?>{y}</affirmative<Yes>.>{n}</negative<No>.>.");
	char print_rules{io.read_repeat("yn")};

	if (print_rules == 'y') {
		std::string rules = "<" + get_rules() + ">.";
		rules = std::regex_replace(rules, std::regex("\\n"), "><");
		io.format_and_print("/box{funky}{light}{center}{left}" + rules);
	}
	
	scenario->begin_game(state);

	if (!state.contains("round")) {
		state.add_entry("round", 1, {true, 300, "Round: "});
	}
	if (!state.contains("round won")) {
		state.add_entry("round won", true, {false});
	}

	bool won = true;

	for (int i = 1; i <= 3 && won; i++) {
		state.set_entry("round", i);
		won = play_round(state, i);
		state.set_entry("round won", won);

		if (won)
			io.format_and_print("/say{game master}</affirmative<You win this round!>.><" + std::to_string(3 - i) + " to go...>.");
		else
			io.format_and_print("/say{game master}</affirmative<You lose the game!>.>.");

		scenario->after_round(state, i);
	}

	if (won)
		scenario->won(state);
	else {
		scenario->lost(state);
		return state;
	}

	go_to_next(state, chain);

	return state;
}

Game::Game(Scenario* scenario) :scenario{scenario}, io{IOManager::access_singleton()} {}

Game::~Game() {
	delete scenario;
}
