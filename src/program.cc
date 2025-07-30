#include "program.h"
#include "baseinterface.h"
#include <print>

namespace skipass {

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
			std::println("USERDEL mode");
			break;
		case Mode::USERPREV:
			m_manager.nextuser();
			break;
		case Mode::USERNEXT:
			m_manager.prevuser();
			break;
		case Mode::BUYTICKET:
			std::println("BUYTICKET mode");
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
