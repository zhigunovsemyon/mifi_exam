#include "client.h"
#include "timelimitedticket.h"
#include "ridelimitedticket.h"
#include <cstdlib>
#include <exception>
#include <memory>
#include <print>

int main()
try {
	auto x = std::make_shared<skipass::Client>(skipass::Client{"s",1,skipass::Client::gender::female});
	skipass::Ticket::RideLimited tl{x};
	std::print("remainder:{}\n", tl.remainder());

	auto exch = tl.refill(200);
	std::print("remainder:{}, exchange:{}\n", tl.remainder(), exch);

	exch = tl.refill(320);
	std::print("remainder:{}, exchange:{}\n", tl.remainder(), exch);

	exch = tl.refill(720);
	std::print("remainder:{}, exchange:{}\n", tl.remainder(), exch);
	return EXIT_SUCCESS;
} catch (std::exception const & e) {
	std::println(stderr, "Исключение с сообщением: {}", e.what());
	return EXIT_FAILURE;
} catch (...) {
	std::println(stderr, "Неизвестное исключение");
	return EXIT_FAILURE;
}
