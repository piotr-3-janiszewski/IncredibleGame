#include <events/GameState.hpp>

#include <sstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

std::string GameState::str() {
	std::ostringstream result_stream;

	result_stream << "/box<";
	if (contains("special ending"))
		result_stream << get_str("special ending") << ">";
	else if (std::get<bool>(get_entry("victory")))
		result_stream << "/affirmative<You won!>.>";
	else if (!std::get<bool>(get_entry("victory")))
		result_stream << "/negative<You lost!>.>";
	
	if (contains("ending description")) {
		result_stream << "</paint{italic}<" << std::get<std::string>(get_entry("ending description")) << ">.>";
	}

	result_stream << "<Game results:>";

	std::vector<std::pair<std::string, EntryConfiguration>> printable_configurations;
	std::copy_if(
	  configuration_entries.begin(), configuration_entries.end(), 
	  std::back_inserter(printable_configurations),
	  [](std::pair<std::string, EntryConfiguration> entry_pair) {
	  	return entry_pair.second.printable;
	});
	
	std::sort(
	  printable_configurations.begin(),
	  printable_configurations.end(),
	  [](const std::pair<std::string, EntryConfiguration>& first,
	     const std::pair<std::string, EntryConfiguration>& second){
		return first.second.print_priority < second.second.print_priority;
	});

	for (const std::pair<std::string, EntryConfiguration>& entry_pair : printable_configurations) {
		result_stream << "<";
		if (entry_pair.second.print_title == "")
			result_stream << entry_pair.first;
		else
			result_stream << entry_pair.second.print_title;
		result_stream << entry_pair.second.begin_value_modificators;

		result_stream << get_str(entry_pair.first);

		result_stream << entry_pair.second.end_value_modificators << ">";
	}
	
	result_stream << ".";

	return result_stream.str();
}

bool GameState::contains(std::string key) {
	return entries.contains(key);
}

void GameState::add_entry(std::string key, Entry value, EntryConfiguration configuration) {
	if (contains(key)) {
		std::cerr << "GameState entry \"" << key << "\" already exists" << std::endl;
		return;
	}
	
	entries[key] = value;
	configuration_entries[key] = configuration;
}

const GameState::Entry& GameState::get_entry(std::string key) {
	if (contains(key) == false) {
		std::cerr << "GameState entry \"" << key << "\" doesn't exist" << std::endl;

		return error_entry;
	}

	return entries[key];
}

void GameState::set_entry(std::string key, Entry entry) {
	if (contains(key) == false) {
		std::cerr << "GameState entry \"" << key << "\" doesn't exist" << std::endl;
		return;
	}

	entries[key] = entry;

	return;
}

std::string GameState::get_str(std::string key) {
	return std::visit<std::string>([](auto&& value) {
		using value_type = std::remove_cvref_t<decltype(value)>;

		if constexpr (std::is_same_v<value_type, std::string>)
			return value;
		else if constexpr (std::is_same_v<value_type, int>)
			return std::to_string(value);
		else if constexpr (std::is_same_v<value_type, bool>)
			return (value ? "yes" : "no");
		else if constexpr (std::is_same_v<value_type, std::monostate>){
			std::cerr << "GameState entry is undefined" << std::endl;
			return "UNDEFINED";
		}
		else {
			std::cerr << "GameState entry Visitor not exhaustive" << std::endl;
			return "ERROR";
		}
	},
	get_entry(key));
}

GameState::EntryConfiguration& GameState::get_entry_configuration(std::string key) {
	if (contains(key) == false) {
		std::cerr << "GameState entry \"" << key << "\" doesn't exist" << std::endl;
		throw "GameState entry" + key + " doesn't exist";
	}

	return configuration_entries[key];
}

GameState::GameState() {
	add_entry("victory", false, {false});
	add_entry("score", 0, {true, 16384, "Score: ", "/paint{bright-yellow}<", ">."});
}

GameState::EntryConfiguration::EntryConfiguration(bool printable, int print_priority, std::string print_title, std::string begin_value_modificators, std::string end_value_modificators) :printable{printable}, print_priority{print_priority}, print_title{print_title}, begin_value_modificators{begin_value_modificators}, end_value_modificators{end_value_modificators} {};
