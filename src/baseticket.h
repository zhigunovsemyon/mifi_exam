#pragma once

namespace skipass::Ticket {

class Base {
	int m_id;
	static int m_id_max; // от нуля (см. baseticket.cc)

public:
	Base() noexcept : m_id{m_id_max++} {}

	int id() const noexcept { return m_id; }
};

} // namespace skipass::Ticket
