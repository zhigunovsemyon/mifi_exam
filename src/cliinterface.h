#pragma once
#include "baseinterface.h"

namespace skipass::Interface {

class CLI : public Base {
public:
	Program::Mode options() const override;

	void show_user_count(size_t count) const override;

	void invalid_user() const override;

	void show_user_info(std::shared_ptr<Client>) const override;

	std::optional<client_t> retrieve_user_info() const override;

	void print_error_message(std::string_view msg) const override;

	int select_new_ticket_type(std::span<std::string_view> typenames) const override;
};

} // namespace skipass::Interface
