#include "cliinterface.h"
#include "client.h"
#include "program.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>

namespace skipass::Interface {

// очистка ввода до \n
static inline void clear_cin()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void show_menu_opts()
{
	std::println("=============================================================");
	std::println("Нажмите c чтобы показать число пользователей");
	std::println("Нажмите a чтобы добавить пользователя");
	std::println("Нажмите d чтобы удалить пользователя");
	std::println("Нажмите n чтобы перейти к следующему пользователю");
	std::println("Нажмите p чтобы перейти к предыдущему пользователю");
	std::println("Нажмите u чтобы просмотреть информацию о текущем пользователе");
	std::println("Нажмите b чтобы купить билет");
	std::println("Нажмите q чтобы выйти");
}

static auto char_to_opt(char c)
{
	using Mode = Program::Mode;
	switch (c) {
	case 'q':
	case 'Q':
		return Mode::EXIT;
	case 'u':
	case 'U':
		return Mode::USERINFO;
	case 'b':
	case 'B':
		return Mode::BUYTICKET;
	case 'p':
	case 'P':
		return Mode::USERPREV;
	case 'n':
	case 'N':
		return Mode::USERNEXT;
	case 'a':
	case 'A':
		return Mode::USERADD;
	case 'd':
	case 'D':
		return Mode::USERDEL;
	case 'c':
	case 'C':
		return Mode::SHOW_USERCOUNT;
	case EOF:
		return Mode::EXIT;
	default:
		return Mode::MENU;
	}
}

void CLI::print_error_message(std::string_view msg) const
{
	std::println(stderr, "Ошибка: {}", msg);
}

Program::Mode CLI::options() const
{
	char c;
	show_menu_opts();

	std::cin >> c;
	if (std::cin.eof())
		c = EOF;

	clear_cin();
	return char_to_opt(c);
}

void CLI::show_user_count(size_t count) const
{
	std::println("В системе {} пользователей", count);
}

void CLI::invalid_user() const
{
	std::println("Пользователь не был выбран!");
}

void CLI::show_user_info(client_t client) const
{
	auto genderText = (client->gender() == Client::gender::male) ? "мужской" : "женский";
	auto ticket = client->assigned_ticket();

	std::println();
	std::println("Информация о текущем пользователе:");
	std::println("Имя: {}", client->name());
	std::println("Возраст: {}", client->age());
	std::println("Пол: {}", genderText);
	if (!ticket)
		std::println("Билет не привязан");
	else
		std::println("Привязанный билет: {}", ticket->type_name());
	std::println();
}

using gender = enum Client::gender;

static std::optional<gender> str_to_gender(std::string_view str)
{
	if (str == "М" || str == "м")
		return Client::gender::male;
	if (str == "ж" || str == "Ж")
		return Client::gender::female;
	return std::nullopt;
};

std::optional<CLI::client_t> CLI::retrieve_user_info() const
{

	std::string name;
	int age;
	char g[3]{};

	std::print("Имя: ");
	std::getline(std::cin, name);
	std::print("Возраст: ");
	std::cin >> age;
	std::print("Пол: М/Ж: ");
	std::cin >> g;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	auto gen = str_to_gender(g);

	if (!std::cin || !gen) {
		print_error_message("ошибка ввода");
		return std::nullopt;
	}

	try {
		return std::make_shared<Client>(name, age, *gen);
	} catch (std::invalid_argument const & argErr) {
		print_error_message(std::string{argErr.what()});
		return std::nullopt;
	}
}

int CLI::select_new_ticket_type(std::span<std::string_view> typenames) const
{
	int ret{-1};
	for(int i{}; auto n : typenames)
		std::println("{}. {}", ++i, n); //счёт от 1
	std::print("-> ");
	std::cin >> ret;
	if(!std::cin || ret < 1)
		return -1;
	if(static_cast<size_t>(ret) > typenames.size())
		return -1;

	return ret - 1;//от нуля (индекс фабрики)
}

} // namespace skipass::Interface
