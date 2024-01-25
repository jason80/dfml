/**
 * @file data.h
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @brief Declaration of the Data class in the context of the Dragonfly Markup Language (DFML).
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <dfml/element.h>
#include <dfml/value.h>

#include <string>

namespace dfml {

/**
 * @brief Class representing a data element in the Dragonfly Markup Language (DFML).
 */
class Data : public Element {
public:
	/**
	 * @brief Default constructor for the Data class.
	 */
	Data() = default;

	/**
	 * @brief Construct a new Data object
	 * 
	 * @param value value object
	 */
	Data(Value value) : value(value) {}

	/**
	 * @brief Creates and returns a shared pointer to an empty Data instance.
	 * 
	 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
	 */
	static std::shared_ptr<Data> create();

	/**
	 * @brief Creates and returns a shared pointer Data instance with the given value.
	 * 
	 * @param value value object.
	 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
	 */
	static std::shared_ptr<Data> create(Value value);

	/**
	 * @brief Creates and returns a shared pointer to a Data instance with the specified string value.
	 * 
	 * @param value The string value of the data.
	 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
	 */
	static std::shared_ptr<Data> create_string(const std::string value);

	/**
	 * @brief Creates and returns a shared pointer to a Data instance with the specified integer value.
	 * 
	 * @param value The integer value of the data.
	 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
	 */
	static std::shared_ptr<Data> create_integer(const long value);

	/**
	 * @brief Creates and returns a shared pointer to a Data instance with the specified double value.
	 * 
	 * @param value The double value of the data.
	 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
	 */
	static std::shared_ptr<Data> create_double(const double value);

	/**
	 * @brief Creates and returns a shared pointer to a Data instance with the specified boolean value.
	 * 
	 * @param value The boolean value of the data.
	 * @return std::shared_ptr<Data> Shared pointer to the new Data instance.
	 */
	static std::shared_ptr<Data> create_boolean(const bool value);

	/**
	 * @brief Gets the element type as an integer, identifying it as data.
	 * 
	 * @return int The element type (DATA).
	 */
	int get_element_type() override { return Element::DATA; }

	/**
	 * @brief Gets the value object associated with the data.
	 * 
	 * @return Value& Reference to the Value object.
	 */
	Value &get_value() { return value; }

private:
	Value value{}; /**< Value object associated with the data. */
};

} // namespace dfml
