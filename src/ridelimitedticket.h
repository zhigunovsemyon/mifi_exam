#pragma once
#include "expirableticket.h"
#include <memory>

namespace skipass::TicketFactory {
class RideLimited;
}

namespace skipass::Ticket {

class RideLimited : public Expirable {
	friend class TicketFactory::RideLimited;
	static constexpr money_t sm_price = 300;
	static constexpr int sm_ridesOfTicket = 7;
	static constexpr auto sm_name{"ограниченный по поездкам"};

	int m_ridesRemainder;

public:
	~RideLimited() override = default;

	RideLimited(pClient_t client) : Expirable(client), m_ridesRemainder(sm_ridesOfTicket) {}

	constexpr money_t price() const override { return sm_price; }

	// Пополнение билета с возвращением сдачи
	change_t refill(money_t m) override;

	// Остаток в виде строки
	std::string remainder() const override;

	constexpr char const * type_name() const override { return sm_name; }
};

} // namespace skipass::Ticket

namespace skipass::TicketFactory {

class RideLimited : public Base {
public:
	using money_t = int;

	// Стоимость билета
	constexpr money_t price() const override { return Ticket::RideLimited::sm_price; }

	// Название типа билета
	constexpr char const * type_name() const override { return Ticket::RideLimited::sm_name; }

	ticket_t sell(std::weak_ptr<Client> client) override { return std::make_shared<Ticket::RideLimited>(client); }
};

} // namespace skipass::TicketFactory
