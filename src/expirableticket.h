#pragma once
#include "baseticket.h"
#include <optional>
#include <string>

namespace skipass::Ticket {

class Expirable : public Base {
public:
	using change_t = money_t;

	Expirable(pClient_t client) : Base{client} {}

	~Expirable() = default;

	// Пополнение билета с возвращением сдачи
	virtual change_t refill(money_t m) = 0;

	// Остаток в виде строки
	virtual std::optional<std::string> remainder() const = 0;
};

} // namespace skipass::Ticket
