#include "clientmanager.h"
#include "client.h"
#include <string_view>

namespace skipass {
using client_t = std::shared_ptr<skipass::Client>;

std::expected<client_t, std::string> ClientManager::adduser(std::string_view name, int age, gender gender)
try {
	client_t client {new Client(name, age, gender)};
	m_storage.push_back(client);
	m_cur = m_storage.end() - 1;
	return client;
} catch (std::invalid_argument const & err) {
	return std::unexpected{err.what()};
}

} // namespace skipass
