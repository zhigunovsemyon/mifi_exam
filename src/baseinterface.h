#pragma once
#include "client.h"
#include "program.h"
#include <cstddef>
#include <memory>
#include <optional>

namespace skipass::Interface {

class Base {
	//+ показать число пользователей
	//+ добавить пользователя
	//+ удалить пользователя
	//+ сменить пользователя
	// купить билет
	// меню
	// пополнить билет
	// проверить остаток
	// открыть/закрыть ячейку
	// получить информацию о номере привязанной ячейки 
	// изменение владельца

public:
	using client_t = std::shared_ptr<Client>;
	~Base() = default;

	virtual Program::Mode options() const = 0;

	virtual void show_user_count(size_t count) const = 0;

	virtual void invalid_user() const = 0;

	virtual void show_user_info(client_t) const = 0;

	virtual std::optional<client_t> retrieve_user_info() const = 0;

	virtual void print_error_message(std::string_view msg) const = 0;
};

} // namespace skipass::Interface
