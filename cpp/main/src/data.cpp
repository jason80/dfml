/**
 * @file data.cpp
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @brief Implementation of the Data class methods in the context of the Dragonfly Markup Language (DFML).
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dfml/data.h>

namespace dfml {

/**
 * @brief Creates and returns a shared pointer to an empty Data instance.
 * 
 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
 */
std::shared_ptr<Data> Data::create() {
	return std::make_shared<Data>();
}

/**
 * @brief Creates and returns a shared pointer Data instance with the given value.
 * 
 * @param value value object.
 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
 */
std::shared_ptr<Data> Data::create(Value value) {
	return std::make_shared<Data>(value);
}

/**
 * @brief Creates and returns a shared pointer to a Data instance with the specified string value.
 * 
 * @param value The string value of the data.
 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
 */
std::shared_ptr<Data> Data::create_string(const std::string value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_string(value);
	return data;
}

/**
 * @brief Creates and returns a shared pointer to a Data instance with the specified integer value.
 * 
 * @param value The integer value of the data.
 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
 */
std::shared_ptr<Data> Data::create_integer(const long value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_integer(value);
	return data;
}

/**
 * @brief Creates and returns a shared pointer to a Data instance with the specified double value.
 * 
 * @param value The double value of the data.
 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
 */
std::shared_ptr<Data> Data::create_double(const double value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_double(value);
	return data;
}

/**
 * @brief Creates and returns a shared pointer to a Data instance with the specified boolean value.
 * 
 * @param value The boolean value of the data.
 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
 */
std::shared_ptr<Data> Data::create_boolean(const bool value) {
	auto data = std::make_shared<Data>();
	data->get_value().set_boolean(value);
	return data;
}

} // namespace dfml
