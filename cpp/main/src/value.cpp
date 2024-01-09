#include <dfml/value.h>

#include <sstream>

namespace dfml {

void Value::set_string(std::string value) {
	this->type = Value::STRING;
	this->value = value;
}

void Value::set_integer(long value) {
	this->type = Value::INTEGER;
	std::stringstream ss;
	ss << value;
	this->value = ss.str();
}

void Value::set_double(double value) {
	this->type = Value::DOUBLE;
	std::stringstream ss;
	ss << value;
	this->value = ss.str();
}

void Value::set_boolean(bool value) {
	this->type = Value::BOOLEAN;
	this->value = value ? "true" : "false";
}

} 
