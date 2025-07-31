#include "cliinterface.h"
#include "program.h"
#include "ridelimitedticket.h"
#include <cassert>
#include <cstdlib>
#include <exception>
#include <print>

int main()
try {
	skipass::TicketFactory::RideLimited rl;
	std::array<skipass::TicketFactory::Base *, 1> ticketFactories{&rl};
	skipass::Interface::CLI ui;
	skipass::Manager manager{ticketFactories};
	skipass::Program{manager, ui}.run();
	return EXIT_SUCCESS;
} catch (std::exception const & e) {
	std::println(stderr, "Исключение с сообщением: {}", e.what());
	return EXIT_FAILURE;
} catch (...) {
	std::println(stderr, "Неизвестное исключение");
	return EXIT_FAILURE;
}
