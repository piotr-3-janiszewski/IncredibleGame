#include <IO/environments/IOLinuxTerminal.hpp>

int main() {
	IOLinuxTerminal terminal;

	terminal.print_formatted("/paint{italic}<Hello!>.");
	terminal.print_formatted("/paint{italic}{green}<Hello!>.");
	terminal.print_formatted("/paint{italic}{green}{bg-blue}<Hello!>.");
	terminal.print_formatted("/paint{italic}{green}{bg-blue}</paint{blink}<Hel>.lo!>.");
}
