add_subdirectory(parser)

add_library(decoratorsio STATIC
	SlashEscapeFormatter.cpp
	WidenFormatter.cpp
	DiceFormatter.cpp
	BoxFormatter.cpp
#	UpperFormatter.cpp
#	LowerFormatter.cpp
	)

target_link_libraries(decoratorsio
	parserio
	utils
	formattedio
	)
