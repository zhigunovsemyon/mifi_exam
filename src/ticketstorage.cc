#include "ticketstorage.h"

namespace skipass {

int TicketStorage::TicketCell::sm_maxCellid{0};

std::optional<int> TicketStorage::insert(pTicket_t ticket)
{
	// итератор на вставленный тикет
	auto inserted = m_storage.insert(ticket).first;
	inserted->m_ptr->change_cell_id(inserted->m_cellid);

	return inserted->m_ptr->cell_id();
}

}
