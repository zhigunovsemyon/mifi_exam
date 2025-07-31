#pragma once
#include "baseticket.h"
#include "clientmanager.h"
#include "ticketstorage.h"
#include <span>

namespace skipass {

class Manager : public TicketStorage, public ClientManager {
	std::span<TicketFactory::Base *> m_ticketFactories;
public:
	Manager(std::span<TicketFactory::Base *> ticketFactories) : m_ticketFactories(ticketFactories) {}
};

} // namespace skipass
