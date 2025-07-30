#pragma once
#include "clientmanager.h"
#include "ticketstorage.h"

namespace skipass {

class Manager : public TicketStorage, public ClientManager {};

} // namespace skipass
