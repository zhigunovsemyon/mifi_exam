#include "clientmanager.h"
#include "client.h"

namespace skipass {
using client_t = std::shared_ptr<skipass::Client>;

void ClientManager::adduser(client_t client)
{
	m_storage.push_back(client);
	m_cur = m_storage.end() - 1;
}

} // namespace skipass
