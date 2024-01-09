#pragma once

#include <dfml_element.h>
#include <dfml_value.h>

#include <string>

namespace dfml {

class Data: public Element {
public:
	Data() = default;

	static std::shared_ptr<Data> create();
	static std::shared_ptr<Data> create_string(const std::string value);
	static std::shared_ptr<Data> create_integer(const long value);
	static std::shared_ptr<Data> create_double(const double value);
	static std::shared_ptr<Data> create_boolean(const bool value);

	int get_element_type() { return Element::DATA; }

	std::string construct(int level);

	Value &get_value() { return value; }

private:
	Value value{};
};

}