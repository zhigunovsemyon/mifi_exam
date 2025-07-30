#include "clientmanager.h"
#include "client.h"

namespace skipass {
using client_t = std::shared_ptr<skipass::Client>;

void ClientManager::adduser(client_t client)
{
	m_storage.push_back(client);
	m_cur = m_storage.end() - 1;
}

void ClientManager::prevuser() noexcept
{
	if (m_cur != m_storage.begin())
		--m_cur;
}

void ClientManager::nextuser() noexcept
{
	if (std::next(m_cur) != m_storage.end())
		++m_cur;
}

void ClientManager::deluser() noexcept
{
	if (m_cur == m_storage.end())
		return;
	m_cur = m_storage.erase(m_cur);
	if (!m_storage.empty() && m_cur == m_storage.end())
		m_cur = m_storage.begin();
}

std::optional<client_t> ClientManager::current()
{
	if (m_storage.end() == m_cur)
		return {};
	return *m_cur;
}

} // namespace skipass
