#include <IO/formatters/CardFormatter.hpp>

#include <IO/IOManager.hpp>

int main() {
	IOManager& io = IOManager::access_singleton();

	io.format_and_print("/hand{2S}{3C}{4D}{5H}{6S}{7C}{8D}{9H}{0S}{JC}{QD}{KH}{AS}{AC}{AD}{AH}.");

	return 0;
}
