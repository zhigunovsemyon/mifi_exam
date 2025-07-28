#pragma once

namespace skipass::Ticket {

class Base {
	int m_id;
	static int m_id_max; // от нуля (см. baseticket.cc)

public:
	Base() noexcept;

	int id() const noexcept;
};

} // namespace skipass::Ticket
