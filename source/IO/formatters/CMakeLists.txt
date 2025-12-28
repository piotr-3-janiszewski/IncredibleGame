add_subdirectory(parser)

add_library(decoratorsio STATIC
	SlashEscapeFormatter.cpp
	WidenFormatter.cpp
	DiceFormatter.cpp
	BoxFormatter.cpp
	LeftOverCommandsFormatter.cpp
	AffirmativeNegativeFormatter.cpp
	RainbowFormatter.cpp
#	UpperFormatter.cpp
#	LowerFormatter.cpp
	)

target_link_libraries(decoratorsio
	parserio
	utils
	formattedio
	)
