#include <utils/test_utils.hpp>
#include <IO/formatters/BoxFormatter.hpp>

int main() {
	BoxFormatter formatter;
	std::cout << formatter.format("/box<><Holis mundo!>.");
	std::cout << formatter.format("/box<><holis...><HOLIS!>.");
	std::cout << formatter.format("/box<><Po deszczu gwiazd><Na łące popiołów><Zebrali się wszyscy><Pod strażą aniołów>.");
	std::cout << formatter.format("/box{double-dash}<><Z tych świątyń><nie widać><nieba...>.");
	std::cout << formatter.format("/box{normal}{heavy}<><To anty-litania chwili>.");
	std::cout << formatter.format("/box{normal}{heavy}{left}<><I z lewej>.");
	std::cout << formatter.format("/box{normal}{heavy}{right}<><I z prawej>.");
	std::cout << formatter.format("/box{normal}{heavy}{justify}<><I po całości>.");
	std::cout << formatter.format("/box{double}{light}{center}<><I'm very double>.");
	std::cout << formatter.format("/box{double}{heavy}{center}<><Same, but now it's!><...><Still the same TwT>.");
	std::cout << formatter.format("/box{funky}<><It'S FUnkY tiME!>.");
	std::cout << formatter.format("/box{cross}<><DEUS><VULT><!!!>.");
	std::cout << formatter.format("/box{cross}{heavy}{center}{left}{60}<><w i d e><DEUS><VULT><!!!>.");
	std::cout << formatter.format("/box{normal}{heavy}{center}{left}{60}<><I don't like unicode>.");
	std::cout << formatter.format("/box{normal}{heavy}{center}{center}{60}<><It's hard>.");
	std::cout << formatter.format("/box{normal}{heavy}{center}{right}{60}<><Especially if you do everything by hand>.");
	std::cout << formatter.format("/box{normal}{heavy}<Potęga smaku><To wcale nie wymagało wielkiego charakteru><nasza odmowa niezgoda i upór><mieliśmy odrobinę koniecznej odwagi><lecz w gruncie rzeczy była to sprawa smaku><Tak smaku><w którym są włókna duszy i chrząstki sumienia>.");
	std::cout << formatter.format("/box{double}{light}{left}<Apollo i Marsjasz><właściwy pojedynek Apollona><z Marsjaszem><(słuch absolutny><kontra ogromna skala)><odbywa się pod wieczór><gdy jak już wiemy><sędziowie><przyznali zwycięstwo bogu>.");
	std::cout << formatter.format("/box{double}{light}{right}{left}<Kowal><Całą bezkształtną masę kruszców drogocennych,><Które zaległy piersi mej głąb nieodgadłą,><Jak wulkan z swych otchłani wyrzucam bezdennych><I ciskam ją na twarde, stalowe kowadło.>.");
	std::cout << formatter.format("/box{dots}{light}{left}{right}<ZABITE DRZEWO><Z ciemnych mojego lasu drzew jedno najcichsze><Ukochałem, najbardziej smutne i najwiotsze:><><Brzozę, co nie szumiała w najszaleńszym wichrze,><Zawsze niema, choć wiatru wiew się o nią otrze.>.");
	
	return -1;
}
