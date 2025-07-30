#include "cliinterface.h"
#include "program.h"
#include <cassert>
#include <cstdlib>
#include <exception>
#include <print>

int main()
try {
	skipass::Interface::CLI ui;
	skipass::Manager manager;
	skipass::Program{manager, ui}.run();
	return EXIT_SUCCESS;
} catch (std::exception const & e) {
	std::println(stderr, "Исключение с сообщением: {}", e.what());
	return EXIT_FAILURE;
} catch (...) {
	std::println(stderr, "Неизвестное исключение");
	return EXIT_FAILURE;
}
