/**
 * @file value.h
 * @brief Declaration of the Value class in the context of the Dragonfly Markup Language (DFML).
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string>

namespace dfml {

/**
 * @brief Class representing a value in the Dragonfly Markup Language (DFML).
 */
class Value {
public:
	/**
	 * @brief Constant representing a string type value.
	 */
	static constexpr int STRING = 0;

	/**
	 * @brief Constant representing an integer type value.
	 */
	static constexpr int INTEGER = 1;

	/**
	 * @brief Constant representing a double type value.
	 */
	static constexpr int DOUBLE = 2;

	/**
	 * @brief Constant representing a boolean type value.
	 */
	static constexpr int BOOLEAN = 3;

	/**
	 * @brief Gets the type of the value.
	 * 
	 * @return const int The type of the value.
	 */
	const int get_type() { return type; };

	/**
	 * @brief Sets the value as a string.
	 * 
	 * @param data The string data to set.
	 */
	void set_string(const std::string data);

	/**
	 * @brief Sets the value as an integer.
	 * 
	 * @param data The integer data to set.
	 */
	void set_integer(long data);

	/**
	 * @brief Sets the value as a double.
	 * 
	 * @param data The double data to set.
	 */
	void set_double(double data);

	/**
	 * @brief Sets the value as a boolean.
	 * 
	 * @param data The boolean data to set.
	 */
	void set_boolean(bool data);

	/**
	 * @brief Gets the string representation of the value.
	 * 
	 * @return const std::string The string representation of the value.
	 */
	const std::string get_value() { return value; };

private:
	int type{}; /**< Type of the value. */
	std::string value{}; /**< String representation of the value. */
};

} // namespace dfml
