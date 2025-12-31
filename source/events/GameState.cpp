#include <events/GameState.hpp>

#include <sstream>
#include <utility>
#include <algorithm>
#include <iterator>

std::string GameState::str() {
	std::ostringstream result_stream;

	result_stream << "/box<";
	if (contains("special ending"))
		result_stream << get_string_entry("special ending") << ">";
	else if (get_bool_entry("victory"))
		result_stream << "/positive<You won!>.>";
	else (get_bool_entry("victory"))
		result_stream << "/negative<You lost!>.>";
	
	if (contains("ending description")) {
		result_stream << "</paint{italic}<" << get_string_entry("ending description") << ">.>";
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
	  [](const std::pair<std::string, EntryConfiguration>& first
	     const std::pair<std::string, EntryConfiguration>& second){
		return first.second.priority
	})

	for (const std::pair<std::string, EntryConfiguration>& entry_pair : printable_configurations) {
		resullt_stream << "<";
		if (entry_pair.second.print_title == "")
			result_stream << entry_pair.first;
		else
			result_stream << entry_pair.second.print_title;
		result_stream << entry_pair.second.begin_value_modificators;

		if (string_entries.contains(entry_pair.first)) {
			result_stream << get_string_entry(entry_pair.first);
		}
		else if (int_entries.contains(entry_pair.first)) {
			result_stream << get_int_entry(entry_pair.first);
		}
		else if (bool_entries.contains(entry_pair.first)) {
			result_stream << (get_bool_entry(entry_pair.first) ? "yes" : "no");
		}
		else {
			result_stream << "ERROR, value not found" << std::endl;
		}

		result_stream << entry_pair.second.end_value_modificators << ">";
	}
	
	result_stream << ".";

	return result_stream.str();
}

bool GameState::contains(std::string key) {
	return string_entries.contains(key) || int_entries.contains(key) || bool_entries.contains(key);
}

void GameState add_entry(std::string key, std::string value, EntryConfiguration configuration) {
	if (contains(key)) {
		std::cerr << "GameState entry \"" << key << "\" already exists" << std::endl;
		return;
	}
	
	string_entries[key] = value;
	configuration_entries[key] = configuration;
}

void GameState add_entry(std::string key, int value, EntryConfiguration configuration) {
	if (contains(key)) {
		std::cerr << "GameState entry \"" << key << "\" already exists" << std::endl;
		return;
	}
	
	int_entries[key] = value;
	configuration_entries[key] = configuration;
}

void GameState add_entry(std::string key, bool value, EntryConfiguration configuration) {
	if (contains(key)) {
		std::cerr << "GameState entry \"" << key << "\" already exists" << std::endl;
		return;
	}
	
	bool_entries[key] = value;
	configuration_entries[key] = configuration;
}

std::string& get_string_entry(std::string key) {
	if (contains(key) == false) {
		std::cerr << "GameState entry \"" << key << "\" doesn't exist" << std::endl;
		return "ERROR";
	}

	return string_entries[key];
}

int& get_string_entry(std::string key) {
	if (contains(key) == false) {
		std::cerr << "GameState entry \"" << key << "\" doesn't exist" << std::endl;
		return "ERROR";
	}

	return int_entries[key];
}

bool& get_string_entry(std::string key) {
	if (contains(key) == false) {
		std::cerr << "GameState entry \"" << key << "\" doesn't exist" << std::endl;
		return "ERROR";
	}

	return bool_entries[key];
}

EntryConfiguration& get_entry_configuration(std::string key) {
	if (contains(key) == false) {
		std::cerr << "GameState entry \"" << key << "\" doesn't exist" << std::endl;
		return "ERROR";
	}

	return configuration_entries[key];
}

GameState::GameState() {
	add_entry("victory", false, {false});
	add_entry("score", 0, {true, 16384, "Score", "/paint{bright-yellow}<", ">."});
}

GameState::EntryConfiguration(bool printable, int print_priority, std::string print_title, std::string begin_value_modificators, std::string end_value_modificators) :printable{printable}, print_priority{print_priority}, print_title{print_title}, begin_value_modificators{begin_value_modificators}, end_value_modificators{end_value_modificators} {};

GameState::EntryConfiguration() : EntryConfiguration(false, 0, "", "", "") {}
