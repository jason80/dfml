/**
 * @file value.cpp
 * @brief Implementation of the Value class methods in the context of the Dragonfly Markup Language (DFML).
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dfml/value.h>

#include <sstream>

namespace dfml {

/**
 * @brief Sets the value as a string.
 * 
 * @param value The string data to set.
 */
void Value::set_string(std::string value) {
	this->type = Value::STRING;
	this->value = value;
}

/**
 * @brief Sets the value as an integer.
 * 
 * @param value The integer data to set.
 */
void Value::set_integer(long value) {
	this->type = Value::INTEGER;
	std::stringstream ss;
	ss << value;
	this->value = ss.str();
}

/**
 * @brief Sets the value as a double.
 * 
 * @param value The double data to set.
 */
void Value::set_double(double value) {
	this->type = Value::DOUBLE;
	std::stringstream ss;
	ss << value;
	this->value = ss.str();
}

/**
 * @brief Sets the value as a boolean.
 * 
 * @param value The boolean data to set.
 */
void Value::set_boolean(bool value) {
	this->type = Value::BOOLEAN;
	this->value = value ? "true" : "false";
}

} // namespace dfml
