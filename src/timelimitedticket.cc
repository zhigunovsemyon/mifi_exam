#include "timelimitedticket.h"
#include <chrono>
#include <format>
#include <optional>

namespace skipass::Ticket {

// Пополнение билета с возвращением сдачи
Expirable::change_t TimeLimited::refill(money_t m)
{
	if (m < sm_price)
		return m;

	m_expireDate += sm_timeOfTicket;
	return refill(m - sm_price); // хвостовая рекурсия
}

// Остаток в виде строки
std::optional<std::string> TimeLimited::remainder() const
{
	auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
	if (now < m_expireDate)
		return std::format("{:%T}", m_expireDate - now);
	else 
		return {};
}

} // namespace skipass::Ticket
