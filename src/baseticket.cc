#include "baseticket.h"

namespace skipass::Ticket {

Base::Base(pClient_t client) noexcept : m_id{m_id_max++} , m_pClient{client}{}

int Base::ticket_id() const noexcept
{
	return m_id;
}

int Base::m_id_max{0};

}
