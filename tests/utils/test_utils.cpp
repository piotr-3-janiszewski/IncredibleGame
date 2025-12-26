#include <utils/test_utils.hpp>

int assert_strings_equal(std::string correct, std::string test_result) {
	if (correct != test_result) {
		std::cout << "Got:" << std::endl;
		std::cout << test_result << std::endl;
		std::cout << "Should be:" << std::endl;
		std::cout << correct << std::endl;
		
		return 1;
	}

	return 0;
}

int assert_true(bool correct, std::string fail_message) {
	if (!correct) {
		std::cout << fail_message << std::endl;
		return -1;
	}

	return 0;
}
