#pragma once

#include <events/Event.hpp>
#include <events/links/Scenario.hpp>

class Game : public Event {
protected:
	Scenario* scenario;
	IOManager& io;
public:
	GameState run(GameState& state, EventChain* chain) override;

	virtual bool play_round(GameState& state, int round) = 0;
	virtual std::string get_rules() = 0;

	Game(Scenario* scenario);
	Game() = delete;
	~Game();
	Game& operator=(Game&) = delete;
	Game(const Game&) = delete;
};
