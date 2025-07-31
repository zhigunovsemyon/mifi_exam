#include "ridelimitedticket.h"
#include <format>

namespace skipass::Ticket {

// Пополнение билета с возвращением сдачи
Expirable::change_t RideLimited::refill(money_t m)
{
	if (m < sm_price)
		return m;

	m_ridesRemainder += sm_ridesOfTicket;
	return refill(m - sm_price); // хвостовая рекурсия
}

// Остаток в виде строки
std::optional<std::string> RideLimited::remainder() const
{
	if (m_ridesRemainder)
		return std::format("{}", m_ridesRemainder);
	else 
		return {};
}

} // namespace skipass::Ticket
