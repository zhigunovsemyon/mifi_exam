#pragma once
#include "baseticket.h"
#include <string>

namespace skipass::Ticket {

class Expirable : Base {
	using change_t = money_t;

public:
	~Expirable() = default;

	// Пополнение билета с возвращением сдачи
	virtual change_t refill(money_t m) = 0;

	// Остаток в виде строки
	virtual std::string remainder() const = 0;
};

}
