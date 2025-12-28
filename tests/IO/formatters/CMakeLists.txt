add_subdirectory(parser)

#[[
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
add_test(NAME SlashEscapeFormatter_I_paid_for_all_the_options_and_Im_going_to_use_them COMMAND eq_SlashEscapeFormatter "///slash./slash.///slash." "/////")
add_test(NAME SlashEscapeFormatter_mix_and_match COMMAND eq_SlashEscapeFormatter "//There is/slash. no //war/slash. in /slash.//Basingse///slash." "/There is/ no /war/ in //Basingse//")

add_executable(eq_log_SlashEscapeFormatter eq_log_SlashEscapeFormatter.cpp)
target_link_libraries(eq_log_SlashEscapeFormatter
	formattedio
	)

add_test(NAME SlashEscapeFormatter_log_empty COMMAND eq_log_SlashEscapeFormatter "" "")
add_test(NAME SlashEscapeFormatter_a_sussy_command COMMAND eq_log_SlashEscapeFormatter "/rayos" "Found 1 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_bad_command COMMAND eq_log_SlashEscapeFormatter "/rayos." "Found an unmatched command: `/rayos.`\n")
add_test(NAME SlashEscapeFormatter_a_lonely_slash COMMAND eq_log_SlashEscapeFormatter "rayos /" "Found 1 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_slash_orgy COMMAND eq_log_SlashEscapeFormatter "/////" "Found 1 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_extroverted_slashes COMMAND eq_log_SlashEscapeFormatter "rayos / / / / /" "Found 5 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_romeo_and_juliett COMMAND eq_log_SlashEscapeFormatter "/feud/" "Found 2 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_bad_command_and_a_lonely_slash COMMAND eq_log_SlashEscapeFormatter "/rayos./" "Found an unmatched command: `/rayos.`\nFound 1 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_three_sussy_commands COMMAND eq_log_SlashEscapeFormatter "/ay /car /amba" "Found 3 unescaped slashes\n")
add_test(NAME SlashEscapeFormatter_three_bad_command COMMAND eq_log_SlashEscapeFormatter "/ay. /car. /amba." "Found an unmatched command: `/ay.`\nFound an unmatched command: `/car.`\nFound an unmatched command: `/amba.`\n")
add_test(NAME SlashEscapeFormatter_sandwich COMMAND eq_log_SlashEscapeFormatter "//ham//" "")
add_test(NAME SlashEscapeFormatter_buisness_as_usuall_in_the_west COMMAND eq_log_SlashEscapeFormatter "// Look /slash. at //our /slash./slash.lush//// syntax." "")
add_test(NAME SlashEscapeFormatter_slash_with_a_mustache COMMAND eq_log_SlashEscapeFormatter "/slash{" "Found an unmatched command: `/slash{`\n")
add_test(NAME SlashEscapeFormatter_nincompoop_barber_shop COMMAND eq_log_SlashEscapeFormatter "/Bob{/slash./Shtephen{///Genovefa{" "Found an unmatched command: `/Bob{`\nFound an unmatched command: `/Shtephen{`\nFound an unmatched command: `/Genovefa{`\n")
]]

add_executable(suite_WidenFormatter_exec suite_WidenFormatter.cpp)
target_link_libraries(suite_WidenFormatter_exec 
	formattedio
	decoratorsio
	testutils
	)
add_test(suite_WidenFormatter suite_WidenFormatter_exec)

add_executable(suite_DiceFormatter_exec suite_DiceFormatter.cpp)
target_link_libraries(suite_DiceFormatter_exec 
	formattedio
	decoratorsio
	testutils
	)
add_test(suite_DiceFormatter suite_DiceFormatter_exec)

add_executable(suite_BoxFormatter_exec suite_BoxFormatter.cpp)
target_link_libraries(suite_BoxFormatter_exec 
	formattedio
	decoratorsio
	testutils
	)
add_test(suite_BoxFormatter suite_BoxFormatter_exec)
