#pragma once
#include "client.h"
#include <expected>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace skipass {

class ClientManager {
	using gender = enum skipass::Client::gender;
	using client_t = std::shared_ptr<skipass::Client>;
	std::vector<client_t> m_storage;

	std::vector<client_t>::iterator m_cur;

public:
	ClientManager() : m_cur{m_storage.end()} {}

	auto usercount() const noexcept { return m_storage.size(); }

	void adduser(client_t);

	void prevuser() noexcept;

	void nextuser() noexcept;

	void deluser() noexcept;

	std::optional<client_t> current();
};

} // namespace skipass
