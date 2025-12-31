#pragma once

#include <string>
#include <unordered_map>

class GameState {
public:
	struct EntryConfiguration {
		bool printable = false;
		int print_priority;
		std::string print_title{};
		std::string begin_value_modificators{};
		std::string end_value_modificators{};

		EntryConfiguration(bool printable, int print_priority, std::string print_title, std::string begin_value_modificators, std::string end_value_modificators);
		EntryConfiguration();
	};

	std::string str();

	void add_entry(std::string key, std::string value, EntryConfiguration configuration = EntryConfiguration{});
	void add_entry(std::string key, int value, EntryConfiguration configuration = EntryConfiguration{});
	void add_entry(std::string key, bool value, EntryConfiguration configuration = EntryConfiguration{});
	std::string& get_string_entry(std::string key);
	int& get_int_entry(std::string key);
	bool& get_bool_entry(std::string key);
	EntryConfiguration& get_entry_configuration(std::string key);

	GameState();
	
private:
	std::unordered_map<std::string, std::string> string_entries;
	std::unordered_map<std::string, int> int_entries;
	std::unordered_map<std::string, bool> bool_entries;

	std::unordered_map<std::string, EntryConfiguration> configuration_entries;

	bool contains(std::string key);
};
