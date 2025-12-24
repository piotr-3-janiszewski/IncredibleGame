#include <IO/formatters/WidenFormatter.hpp>
#include <utils/test_utils.hpp>

int main() {
	WidenFormatter formatter;

	return 
		assert_strings_equal("D z i e ń   d o b r y", formatter.format("/widen<Dzień dobry>.")) ||
		assert_strings_equal("¡Buenos  d í a s  compañero!", formatter.format("¡Buenos/widen< días >.compañero!")) ||
		assert_strings_equal("Теперь время на/paint{red}<  р а с к о л б а с>....", formatter.format("Теперь время на/widen</paint{red}< расколбас>.>...."));
}
