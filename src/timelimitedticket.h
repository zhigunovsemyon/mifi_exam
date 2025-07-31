#pragma once
#include "expirableticket.h"
#include <chrono>

namespace skipass::TicketFactory {
class TimeLimited;
}

namespace skipass::Ticket {

class TimeLimited : public Expirable {
	friend class TicketFactory::TimeLimited;
	static constexpr auto sm_name{"ограниченный по времени"};
	static constexpr money_t sm_price = 300;
	static constexpr std::chrono::seconds sm_timeOfTicket = std::chrono::days(1) - std::chrono::seconds(1);

	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> m_expireDate;

public:
	~TimeLimited() override = default;

	TimeLimited(pClient_t client) : Expirable(client), m_expireDate(sm_timeOfTicket)
	{
	}

	constexpr money_t price() const override { return sm_price; }

	// Пополнение билета с возвращением сдачи
	change_t refill(money_t m) override;

	// Остаток в виде строки
	std::optional<std::string> remainder() const override;

	constexpr char const * type_name() const override { return sm_name; }
};

} // namespace skipass::Ticket

namespace skipass::TicketFactory {

class TimeLimited : public Base {
public:
	using money_t = int;

	// Стоимость билета
	constexpr money_t price() const override { return Ticket::TimeLimited::sm_price; }

	// Название типа билета
	constexpr char const * type_name() const override { return Ticket::TimeLimited::sm_name; }

	ticket_t sell(std::weak_ptr<Client> client) override { return std::make_shared<Ticket::TimeLimited>(client); }
};

} // namespace skipass::TicketFactory
