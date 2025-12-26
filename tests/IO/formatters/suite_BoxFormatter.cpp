#include <utils/test_utils.hpp>
#include <IO/formatters/BoxFormatter.hpp>

int main() {
	BoxFormatter formatter;
	std::cout << formatter.format("/box<Holis mundo!>.");
	std::cout << formatter.format("/box<holis...><HOLIS!>.");
	std::cout << formatter.format("/box<Po deszczu gwiazd><Na łące popiołów><Zebrali się wszyscy><Pod strażą aniołów>.");
	std::cout << formatter.format("/box{double-dash}<Z tych świątyń><nie widać><nieba...>.");
	std::cout << formatter.format("/box{normal}{heavy}<To anty-litania chwili>.");
	std::cout << formatter.format("/box{normal}{heavy}{left}<I z lewej>.");
	std::cout << formatter.format("/box{normal}{heavy}{right}<I z prawej>.");
	std::cout << formatter.format("/box{normal}{heavy}{justify}<I po całości>.");
	std::cout << formatter.format("/box{double}{light}{center}<I'm very double>.");
	std::cout << formatter.format("/box{double}{heavy}{center}<Same, but now it's!><...><Still the same TwT>.");
	std::cout << formatter.format("/box{funky}<It'S FUnkY tiME!>.");
	std::cout << formatter.format("/box{cross}<DEUS><VULT><!!!>.");
	std::cout << formatter.format("/box{cross}{heavy}{center}{left}{60}<w i d e><DEUS><VULT><!!!>.");
	std::cout << formatter.format("/box{normal}{heavy}{center}{left}{60}<I don't like unicode>.");
	std::cout << formatter.format("/box{normal}{heavy}{center}{center}{60}<It's hard>.");
	std::cout << formatter.format("/box{normal}{heavy}{center}{right}{60}<Especially if you do everything by hand>.");

	return 0;
}
