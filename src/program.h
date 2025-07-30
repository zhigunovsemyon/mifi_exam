#pragma once

#include "manager.h"

namespace skipass {

namespace Interface {
class Base;
}

class Program {
public:
	enum class Mode : char {
		EXIT,
		MENU,
		SHOW_USERCOUNT,
		USERADD,
		USERDEL,
		USERINFO,
		USERNEXT,
		USERPREV,
		BUYTICKET
	};

private:
	Manager & m_manager;
	Interface::Base & m_ui;
	Mode m_mode;

public:
	Program(Manager & m, Interface::Base & ui) noexcept : m_manager(m), m_ui(ui), m_mode(Mode::MENU) {}

	Program(Manager && m, Interface::Base && ui) noexcept : m_manager(m), m_ui(ui), m_mode(Mode::MENU) {}

	void run();
};

} // namespace skipass
