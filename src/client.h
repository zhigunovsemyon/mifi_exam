#pragma once
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>

namespace skipass {

class Client {
public:
	enum class gender : int8_t {
		male,
		female
	};

private:
	std::string m_name;
	int8_t m_age;
	gender m_gender;

public:
	Client(std::string_view name, int age, gender gender) : m_name(name), m_gender(gender)
	{
		if (m_name.empty())
			throw std::invalid_argument{"Не указано ФИО!"};

		if (age <= 0 || std::numeric_limits<int8_t>().max() < age)
			throw std::invalid_argument{"Неправильно указан возраст!"};
		else
			m_age = (int8_t)age;
	}

	std::string_view name() const { return m_name; }

	int8_t age() const noexcept { return m_age; }

	gender gender() const noexcept { return m_gender; }
};

} // namespace skipass
