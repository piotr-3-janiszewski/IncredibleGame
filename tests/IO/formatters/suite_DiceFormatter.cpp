#include <IO/formatters/DiceFormatter.hpp>
#include <utils/test_utils.hpp>

int main() {
	DiceFormatter formatter;

	std::cout << formatter.format("/roll{d6}{1}{2}{3}{4}{5}{6}.");
	std::cout.flush();
	std::cout << formatter.format("/roll{d8}{1}{2}{3}{4}{5}{6}{7}{8}.");
	std::cout.flush();
	std::cout << formatter.format("/roll{d10}{2}{6}{7}{10}.");
	std::cout.flush();
	std::cout << formatter.format("/roll{d12}{2}{6}{7}{12}.");
	std::cout.flush();
	std::cout << formatter.format("/roll{d20}{2}{6}{7}{15}{20}.");
	std::cout.flush();

	return 0;
}
