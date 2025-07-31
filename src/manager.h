#pragma once
#include "baseticket.h"
#include "clientmanager.h"
#include "ticketstorage.h"
#include <span>

namespace skipass {

class Manager : public TicketStorage, public ClientManager {
public:
	std::span<TicketFactory::Base *> m_ticketFactories;

	Manager(std::span<TicketFactory::Base *> ticketFactories) : m_ticketFactories(ticketFactories) {}

	//вернуть доступ к фабрикам и названиям
};

} // namespace skipass
