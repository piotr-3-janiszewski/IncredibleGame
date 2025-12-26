add_library(testutils STATIC
	test_utils.cpp
	)

add_executable(suite_UTF_8_utils_exec
	suite_UTF_8_utils.cpp
	)
target_link_libraries(suite_UTF_8_utils_exec
	utils
	testutils
	)
add_test(suite_UTF_8_utils suite_UTF_8_utils_exec)

