#include <utils/UTF_8_utils.hpp>

bool is_continuation_byte(char byte) {
	unsigned unsigned_byte = *reinterpret_cast<unsigned char*>(&byte);

	return (unsigned_byte >= 0x80 && unsigned_byte <= 0xBF);
}

std::string::size_type count_code_points(const std::string& to_count) {
	std::string::size_type code_points = 0;
	for (const char& character : to_count)
		if (!is_continuation_byte(character))
			code_points++;
	
	return code_points;
}
