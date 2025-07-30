#pragma once
#include "baseticket.h"
#include <flat_set>
#include <memory>

namespace skipass {

class TicketStorage {
	using pTicket_t = std::shared_ptr<skipass::Ticket::Base>;

	struct TicketCell {
		static int sm_maxCellid; // от нуля (см. ticketstorage.cc)

		pTicket_t m_ptr;
		int m_cellid;
		bool m_open;

		TicketCell(pTicket_t & ptr) : m_ptr(ptr), m_cellid(sm_maxCellid++), m_open(true) {}

		// int cell_id() const noexcept { return m_cellid; }
		//
		// bool is_open() const noexcept { return m_open; }
		//
		// TicketCell & open() noexcept
		// {
		// 	m_open = true;
		// 	return *this;
		// }
		//
		// TicketCell & close() noexcept
		// {
		// 	m_open = false;
		// 	return *this;
		// }
	};

	struct TicketSort {
		bool operator()(TicketCell const & x, TicketCell const & y) const
		{
			auto const &a = *x.m_ptr.get(), &b = *y.m_ptr.get();

			auto const type_cmp_res = typeid(a).hash_code() <=> typeid(b).hash_code();

			return type_cmp_res == std::strong_ordering::equal ? a.ticket_id() < b.ticket_id()
									   : type_cmp_res == std::strong_ordering::less;
		}
	};

	std::flat_set<TicketCell, TicketSort> m_storage;

public:
	std::optional<int> insert(pTicket_t ticket);
};

} // namespace skipass
