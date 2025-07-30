#include "ticketstorage.h"
#include <algorithm>

namespace skipass {

int TicketStorage::TicketCell::sm_maxCellid{0};

std::optional<int> TicketStorage::insert(pTicket_t ticket)
{
	// итератор на вставленный тикет
	auto inserted = m_storage.insert(TicketCell(ticket, TicketCell::sm_maxCellid++, true)).first;
	inserted->m_ptr->change_cell_id(inserted->m_cellid);

	return inserted->m_ptr->cell_id();
}

std::optional<bool> TicketStorage::is_open(int cellid) const noexcept
{
	auto cellid_equals = [&cellid](TicketCell const & c) { return cellid == c.m_cellid; };
	auto res = std::ranges::find_if(m_storage, cellid_equals);

	if (res == m_storage.cend())
		return {};
	return res->m_open;
}

void TicketStorage::open(int cellid)
{
	auto cellid_equals = [&cellid](TicketCell const & c) { return cellid == c.m_cellid; };
	auto res = std::find_if(m_storage.begin(), m_storage.end(), cellid_equals);

	if (res == m_storage.end())
		return;
	if (res->m_open)
		return;

	auto copy = *res;
	m_storage.erase(res);
	copy.m_open = true;
	m_storage.insert(copy);
}

void TicketStorage::close(int cellid)
{
	auto cellid_equals = [&cellid](TicketCell const & c) { return cellid == c.m_cellid; };
	auto res = std::find_if(m_storage.begin(), m_storage.end(), cellid_equals);

	if (res == m_storage.end())
		return;
	if (!res->m_open)
		return;

	auto copy = *res;
	m_storage.erase(res);
	copy.m_open = false;
	m_storage.insert(copy);
}

} // namespace skipass
