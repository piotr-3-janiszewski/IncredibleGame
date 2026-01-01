add_subdirectory(games)

add_executable(suite_Deck_exec suite_Deck.cpp)
target_link_libraries(suite_Deck_exec
	events
	)
add_test(suite_Deck suite_Deck_exec)
