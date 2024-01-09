#pragma once

#include <string>

namespace dfml {

class Value {
public:
	static constexpr int STRING = 0;
	static constexpr int INTEGER = 1;
	static constexpr int DOUBLE = 2;
	static constexpr int BOOLEAN = 3;

	int get_type() { return type; }

	void set_string(const std::string data);
	void set_integer(long data);
	void set_double(double data);
	void set_boolean(bool data);

	std::string construct();

private:
	int type{};
	std::string value{};
};

}
