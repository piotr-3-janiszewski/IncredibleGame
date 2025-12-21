add_executable(eq_SlashEscapeFormatter eq_SlashEscapeFormatter.cpp)
target_link_libraries(eq_SlashEscapeFormatter 
	formattedio
	)

add_test(NAME SlashEscapeFormatter_empty COMMAND eq_SlashEscapeFormatter "" "")
add_test(NAME SlashEscapeFormatter_no_format COMMAND eq_SlashEscapeFormatter "Vanitas peccata mundi" "Vanitas peccata mundi")
add_test(NAME SlashEscapeFormatter_escape_one_slash COMMAND eq_SlashEscapeFormatter "//Vanitas peccata mundi" "/Vanitas peccata mundi")
add_test(NAME SlashEscapeFormatter_escape_three_slashes COMMAND eq_SlashEscapeFormatter "//Vanitas //peccata //mundi" "/Vanitas /peccata /mundi")
add_test(NAME SlashEscapeFormatter_lonely_slash COMMAND eq_SlashEscapeFormatter "Vanitas /peccata mundi" "Vanitas /peccata mundi")
add_test(NAME SlashEscapeFormatter_tripple_slash COMMAND eq_SlashEscapeFormatter "Vanitas ///peccata mundi" "Vanitas //peccata mundi")
add_test(NAME SlashEscapeFormatter_only_slash COMMAND eq_SlashEscapeFormatter "/" "/")
add_test(NAME SlashEscapeFormatter_four_slashes COMMAND eq_SlashEscapeFormatter "////" "//")

add_executable(eq_log_SlashEscapeFormatter eq_log_SlashEscapeFormatter.cpp)
target_link_libraries(eq_log_SlashEscapeFormatter
	formattedio
	)

add_test(NAME SlashEscapeFormatter_log_empty COMMAND eq_log_SlashEscapeFormatter "" "")
add_test(NAME SlashEscapeFormatter_bad_command COMMAND eq_log_SlashEscapeFormatter "/rayos" "Found an unmatched command: `/rayos`\n")
add_test(NAME SlashEscapeFormatter_a_lonely_slash COMMAND eq_log_SlashEscapeFormatter "rayos /" "Found 1 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_slash_orgy COMMAND eq_log_SlashEscapeFormatter "/////" "Found 1 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_extroverted_slashes COMMAND eq_log_SlashEscapeFormatter "rayos / / / / /" "Found 5 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_bad_command_and_a_lonely_slash COMMAND eq_log_SlashEscapeFormatter "/rayos/" "Found an unmatched command: `/rayos`\nFound 1 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_three_bad_command COMMAND eq_log_SlashEscapeFormatter "/ay /car /amba" "Found an unmatched command: `/ay`\nFound an unmatched command: `/car`\nFound an unmatched command: `/amba`\n")
add_test(NAME SlashEscapeFormatter_sandwich COMMAND eq_log_SlashEscapeFormatter "//ham//" "")

