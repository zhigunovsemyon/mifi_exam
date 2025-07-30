#pragma once
#include "client.h"
#include <memory>
#include <optional>

namespace skipass::Ticket {

class Base {
public:
	using pClient_t = std::weak_ptr<skipass::Client>;
	using money_t = int;

private:
	int m_id;
	static int m_id_max; // от нуля (см. baseticket.cc)

	pClient_t m_pClient;
	int m_cellid{-1};

public:
	virtual ~Base() = default;

	Base(pClient_t client) noexcept;
	
	// Стоимость билета
	constexpr virtual money_t price() const = 0;

	int ticket_id() const noexcept;

	std::optional<int> cell_id() const noexcept;

	void change_cell_id(int newCellid) noexcept {m_cellid = newCellid;}
};

} // namespace skipass::Ticket
