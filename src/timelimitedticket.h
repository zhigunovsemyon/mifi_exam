#pragma once
#include "expirableticket.h"
#include <chrono>

namespace skipass::Ticket {

class TimeLimited : public Expirable {
	static constexpr money_t sm_price = 300;
	static constexpr std::chrono::seconds sm_timeOfTicket = std::chrono::days(1) - std::chrono::seconds(1);

	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> m_expireDate;

public:
	~TimeLimited() override = default;

	TimeLimited()
		: m_expireDate(sm_timeOfTicket +
			       std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()))
	{
	}

	constexpr money_t price() const override { return sm_price; }

	// Пополнение билета с возвращением сдачи
	change_t refill(money_t m) override;

	// Остаток в виде строки
	std::string remainder() const override;
};

} // namespace skipass::Ticket
