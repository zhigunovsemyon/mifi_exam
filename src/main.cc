#include "clientmanager.h"
#include "ridelimitedticket.h"
#include "ticketstorage.h"
#include "timelimitedticket.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <print>
#include <string>

int main()
try {
	skipass::ClientManager cm;
	do {
		std::println("Пользователей в системе: {}", cm.usercount());
		std::string name;
		int age;
		char g;

		std::print("Имя: ");
		std::getline(std::cin, name);
		std::print("Возраст: ");
		std::cin >> age;
		std::print("m/f: ");
		std::cin >> g;
		if (!std::cin)
			break;
		if (!(g == 'm' || g == 'f')) {
			std::println("char: {}({})", g, (int)g);
			break;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		auto ret = cm.adduser(name, age, g == 'm' ? skipass::Client::gender::male : skipass::Client::gender::female);
		if (!ret)
			std::println(stderr, "{}", ret.error());
	} while (true);
	// skipass::TicketStorage st;
	// for (int i = 0; i < 100; ++i) {
	// 	auto x = std::make_shared<skipass::Client>("s", 8, skipass::Client::gender::male);
	// 	std::shared_ptr<skipass::Ticket::Base> t;
	// 	if (i % 2)
	// 		t = std::make_shared<skipass::Ticket::RideLimited>(x);
	// 	else
	// 		t = std::make_shared<skipass::Ticket::TimeLimited>(x);
	//
	// 	st.insert(t);
	// 	if (i % 3)
	// 		st.close(*t->cell_id());
	//
	// }

	// std::ranges::for_each(st.m_storage, [&](skipass::TicketStorage::TicketCell const & c) {
	// 	auto ticket = c.m_ptr.get();
	// 	auto cell_id_from_ticket = *ticket->cell_id();
	// 	assert(cell_id_from_ticket == c.m_cellid);
	//
	// 	std::print("cell_id: {}, ", c.m_cellid);
	// 	std::print("ticket_id: {} ", ticket->ticket_id());
	// 	std::print("Остаток: {}", dynamic_cast<skipass::Ticket::Expirable *>(ticket)->remainder());
	// 	auto open = *st.is_open(cell_id_from_ticket);
	// 	std::print(" Открыт?: {}", open);
	// 	std::println();
	// });
	return EXIT_SUCCESS;
} catch (std::exception const & e) {
	std::println(stderr, "Исключение с сообщением: {}", e.what());
	return EXIT_FAILURE;
} catch (...) {
	std::println(stderr, "Неизвестное исключение");
	return EXIT_FAILURE;
}
