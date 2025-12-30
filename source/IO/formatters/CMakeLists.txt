add_subdirectory(parser)

add_library(decoratorsio STATIC
	SlashEscapeFormatter.cpp
	WidenFormatter.cpp
	DiceFormatter.cpp
	CardFormatter.cpp
	BoxFormatter.cpp
	LeftOverCommandsFormatter.cpp
	AffirmativeNegativeFormatter.cpp
	RainbowFormatter.cpp
	ChoiceFormatter.cpp
	DialogueFormatter.cpp
#	UpperFormatter.cpp
#	LowerFormatter.cpp
	)

target_link_libraries(decoratorsio
	parserio
	utils
	formattedio
	)
