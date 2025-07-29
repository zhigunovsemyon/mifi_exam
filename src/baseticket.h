#pragma once

namespace skipass::Ticket {

class Base {
	int m_id;
	static int m_id_max; // от нуля (см. baseticket.cc)

public:
	using money_t = int;

	virtual ~Base() = default;

	Base() noexcept;
	
	// Стоимость билета
	constexpr virtual money_t price() const = 0;


	int id() const noexcept;
};

} // namespace skipass::Ticket
