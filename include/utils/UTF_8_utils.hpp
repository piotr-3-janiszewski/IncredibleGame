#pragma once

#include <string>

bool is_continuation_byte(char byte);
std::string::size_type count_code_points(const std::string& to_count);
