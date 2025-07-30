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

	std::optional<bool> is_open(int cellid) const noexcept;

	void open(int cellid);

	void close(int cellid);
};

} // namespace skipass
