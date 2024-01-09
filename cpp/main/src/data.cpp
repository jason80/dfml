#include <dfml/data.h>

#include <sstream>

namespace dfml {

std::shared_ptr<Data> Data::create() {
	return std::make_shared<Data>();
}

std::shared_ptr<Data> Data::create_string(const std::string value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_string(value);
	return data;
}

std::shared_ptr<Data> Data::create_integer(const long value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_integer(value);
	return data;
}

std::shared_ptr<Data> Data::create_double(const double value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_double(value);
	return data;
}

std::shared_ptr<Data> Data::create_boolean(const bool value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_boolean(value);
	return data;
}

}
