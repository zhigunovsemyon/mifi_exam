#include "baseticket.h"

namespace skipass::Ticket {

Base::Base() noexcept : m_id{m_id_max++} {}

int Base::id() const noexcept
{
	return m_id;
}

int Base::m_id_max{0};

}