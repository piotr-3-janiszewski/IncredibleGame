add_subdirectory(parser)

set(FONTS_DIRECTORY_PARENT ${CMAKE_SOURCE_DIR})

add_compile_definitions(FONTS_DIRECTORY_PARENT="${FONTS_DIRECTORY_PARENT}")

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
	BannerFormatter.cpp
#	UpperFormatter.cpp
#	LowerFormatter.cpp
	)

target_link_libraries(decoratorsio
	parserio
	utils
	formattedio
	)
