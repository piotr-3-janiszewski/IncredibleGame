add_subdirectory(parser)

add_library(decoratorsio STATIC
	SlashEscapeFormatter.cpp
	WidenFormatter.cpp
#	UpperFormatter.cpp
#	LowerFormatter.cpp
	)

target_link_libraries(decoratorsio
	parserio
	)
