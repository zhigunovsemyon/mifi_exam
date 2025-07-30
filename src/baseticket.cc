#include "baseticket.h"

namespace skipass::Ticket {

Base::Base(pClient_t client) noexcept : m_id{m_id_max++}, m_pClient{client} {}

std::optional<int> Base::cell_id() const noexcept
{
	if (m_cellid < 0)
		return std::nullopt;
	return m_cellid;
}

int Base::ticket_id() const noexcept
{
	return m_id;
}

int Base::m_id_max{0};

} // namespace skipass::Ticket
