#pragma once
#include "client.h"
#include <expected>
#include <memory>
#include <optional>
#include <stdexcept>
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

	std::expected<client_t, char const *> adduser(std::string_view name, int age, gender gender);

	void prevuser() noexcept
	{
		if (m_cur != m_storage.begin())
			--m_cur;
	}

	void nextuser() noexcept
	{
		if (std::next(m_cur) != m_storage.end())
			++m_cur;
	}

	void deluser() noexcept
	{
		m_cur = m_storage.erase(m_cur);
		if (!m_storage.empty() && m_cur == m_storage.end())
			m_cur = m_storage.begin();
	}

	std::optional<client_t> current()
	{
		if (m_storage.end() == m_cur)
			return {};
		return *m_cur;
	}
};

} // namespace skipass
