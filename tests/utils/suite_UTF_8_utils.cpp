#include <utils/UTF_8_utils.hpp>
#include <utils/test_utils.hpp>

#include <iostream>

int main() {
	int r = 0;
	
	std::string jazn = "jaźń";
	r|= assert_true(!is_continuation_byte(jazn[0]), "j is not a continuation byte");
	r|= assert_true(!is_continuation_byte(jazn[1]), "a is not a continuation byte");
	r|= assert_true(!is_continuation_byte(jazn[2]), "first byte in ź is not a continuation byte");
	r|=assert_true(is_continuation_byte(jazn[3]), "second byte in ź is a continuation byte");
	r|=assert_true(!is_continuation_byte(jazn[4]), "first byte in ń is a not continuation byte");
	r|=assert_true(is_continuation_byte(jazn[5]), "second byte in ń is a continuation byte");
	if (r != 0)
		return r;

	std::string zolc = "żółć";
	std::cout << "Counting code points in: " << jazn << std::endl;
	r|=assert_strings_equal("4", std::to_string(count_code_points(jazn)));

	std::cout << "Counting code points in: " <<  zolc << std::endl;
	r|=assert_strings_equal("4", std::to_string(count_code_points(zolc)));

	std::cout << "Counting code points in: ó" << std::endl;
	r|=assert_strings_equal("1", std::to_string(count_code_points("ó")));

	return r;
}
