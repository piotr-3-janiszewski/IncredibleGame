#include <IO/IOManager.hpp>

int main() {
	IOManager& io = IOManager::access_singleton();

	io.format_and_print("/banner{default}{A}.");
	io.format_and_print("/banner{default}{WITAJ OKRUTNA ZIEMIO!}.");
	io.format_and_print("/banner{default}{WITAJ}{OKRUTNA}{ZIEMIO!}.");

	io.format_and_print("/banner{default}{WITAJ}.\n");
	io.format_and_print("/banner{default}{OKRUTNA}.\n");
	io.format_and_print("/banner{default}{ZIEMIO!}.\n");

	return 0;
}
