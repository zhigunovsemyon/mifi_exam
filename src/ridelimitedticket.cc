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
std::string RideLimited::remainder() const
{
	return std::format("Осталось: {}", m_ridesRemainder);
}

} // namespace skipass::Ticket
