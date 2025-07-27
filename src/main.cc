#include "baseticket.h"
#include <cstdlib>
#include <exception>
#include <print>

int main()
try {
	for (int i{}; i < 100; ++i) {
		std::print("id:{} ", skipass::Ticket::Base{}.id());
	}
	std::println("Hello World");
	return EXIT_SUCCESS;
} catch (std::exception const & e) {
	std::println(stderr, "Исключение с сообщением: {}", e.what());
	return EXIT_FAILURE;
} catch (...) {
	std::println(stderr, "Неизвестное исключение");
	return EXIT_FAILURE;
}
