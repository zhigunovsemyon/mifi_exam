#pragma once
#include "expirableticket.h"

namespace skipass::Ticket {

class RideLimited : public Expirable {
	static constexpr money_t sm_price = 300;
	static constexpr int sm_ridesOfTicket = 7;

	int m_ridesRemainder;

public:
	~RideLimited() override = default;

	RideLimited(pClient_t client) : Expirable(client), m_ridesRemainder(sm_ridesOfTicket) {}

	constexpr money_t price() const override { return sm_price; }

	// Пополнение билета с возвращением сдачи
	change_t refill(money_t m) override;

	// Остаток в виде строки
	std::string remainder() const override;
};

} // namespace skipass::Ticket
