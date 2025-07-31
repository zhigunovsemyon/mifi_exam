#include "program.h"
#include "baseinterface.h"
#include <algorithm>
#include <cassert>
#include <string_view>

namespace skipass {

void Program::ticket_buying()
{
	auto usr = m_manager.current();
	if (!usr) {
		m_ui.print_error_message("Не выбран пользователь для покупки!");
		return;
	}

	std::vector<std::string_view> names;
	names.reserve(m_manager.m_ticketFactories.size());
	std::ranges::for_each(m_manager.m_ticketFactories, [&names](auto fac) { names.push_back(fac->type_name()); });

	auto index = m_ui.select_new_ticket_type(names);
	if (index < 0) {
		m_ui.print_error_message("Билет не выбран!");
		return;
	}
	assert(static_cast<size_t>(index) < m_manager.m_ticketFactories.size());
	(*usr)->add_ticket(m_manager.m_ticketFactories[static_cast<size_t>(index)]->sell(*usr));
}

void Program::run()
{
	do {
		switch (m_mode) {
		case Mode::USERINFO: {
			auto curuser = m_manager.current();
			if (!curuser)
				m_ui.invalid_user();
			else
				m_ui.show_user_info(*curuser);
		} break;
		case Mode::EXIT:
			return;
		case Mode::USERADD: {
			auto usr = m_ui.retrieve_user_info();
			if (!usr)
				m_ui.print_error_message("Не удалось создать пользователя!");
			else
				m_manager.adduser(*usr);
		} break;
		case Mode::USERDEL:
			m_manager.deluser();
			break;
		case Mode::USERPREV:
			m_manager.nextuser();
			break;
		case Mode::USERNEXT:
			m_manager.prevuser();
			break;
		case Mode::BUYTICKET:
			ticket_buying();
			break;
		case Mode::MENU:
			m_mode = m_ui.options();
			continue; // пропуск возвращения MENU режима
		case Mode::SHOW_USERCOUNT:
			m_ui.show_user_count(m_manager.usercount());
			break;
		}
		m_mode = Mode::MENU;
	} while (true);
}

} // namespace skipass
