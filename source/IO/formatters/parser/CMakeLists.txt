add_library(parserio STATIC
	Argument.cpp
	Command.cpp
	CommandParser.cpp
	ParsingFormatterTemplate.cpp
	)

target_link_libraries(parserio
	utils
	)
