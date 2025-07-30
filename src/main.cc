#include "client.h"
#include "ridelimitedticket.h"
#include "ticketstorage.h"
#include "timelimitedticket.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <exception>
#include <memory>
#include <print>

int main()
try {
	skipass::TicketStorage st;
	for (int i = 0; i < 100; ++i) {
		auto x = std::make_shared<skipass::Client>("s", 8, skipass::Client::gender::male);
		std::shared_ptr<skipass::Ticket::Base> t;
		if (i % 2)
			t = std::make_shared<skipass::Ticket::RideLimited>(x);
		else
			t = std::make_shared<skipass::Ticket::TimeLimited>(x);

		st.insert(t);
		if (i % 3)
			st.close(*t->cell_id());

	}

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
