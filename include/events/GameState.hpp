#pragma once

#include <string>
#include <variant>
#include <unordered_map>

class GameState {
public:
	using Entry = std::variant<std::monostate, std::string, bool, int>;

	struct EntryConfiguration {
		bool printable = false;
		int print_priority;
		std::string print_title{};
		std::string begin_value_modificators{};
		std::string end_value_modificators{};

		EntryConfiguration(bool printable = false, int print_priority = 0, std::string print_title = "", std::string begin_value_modificators = "", std::string end_value_modificators = "");
	};

	std::string str();

	void add_entry(std::string key, Entry value, EntryConfiguration configuration = EntryConfiguration{});
	const Entry& get_entry(std::string key);
	void set_entry(std::string key, Entry entry);
	void set_if_absent(std::string key, Entry entry);
	void create_or_update(std::string key, Entry entry);
	bool contains(std::string key);
	std::string get_str(std::string key);
	EntryConfiguration& get_entry_configuration(std::string key);

	GameState();
	
private:
	std::unordered_map<std::string, Entry> entries;
	std::unordered_map<std::string, EntryConfiguration> configuration_entries;

	const Entry error_entry{std::monostate{}};
};
