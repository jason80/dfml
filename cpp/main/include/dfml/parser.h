/**
 * @file parser.h
 * @brief Declaration of the Parser class in the context of the Dragonfly Markup Language (DFML).
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @date 2024-01-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string>
#include <memory>
#include <list>
#include <cctype>

namespace dfml {

class Element;
class Data;

/**
 * @brief Iterator for characters used by the Parser to iterate over a string.
 */
class CharIterator {
public:
	CharIterator() = default;

	/**
	 * @brief Sets the data for iteration.
	 * 
	 * @param data The string data to iterate over.
	 */
	void set_data(const std::string data) { this->data = data; }

	/**
	 * @brief Retrieves the next character in the iteration.
	 * 
	 * @return int The ASCII value of the next character.
	 */
	int next();

	/**
	 * @brief Retrieves the current character in the iteration.
	 * 
	 * @return int The ASCII value of the current character.
	 */
	int current() { return data[i - 1]; }

	/**
	 * @brief Moves the iterator back to the previous character.
	 */
	void back();

	/**
	 * @brief Checks if the end of the iteration is reached.
	 * 
	 * @return bool True if the end is reached, false otherwise.
	 */
	bool end() { return i >= data.size(); }

private:
	std::string data;         /**< The string data to iterate over. */
	unsigned long i{};        /**< Current index in the iteration. */
};

/**
 * @brief Class responsible for parsing DFML data and creating Element objects.
 */
class Parser {
public:
	/**
	 * @brief Constructor for the Parser class.
	 * 
	 * @param data The DFML data to parse.
	 */
	Parser(const std::string data);

	/**
	 * @brief Creates and returns a shared pointer to a Parser instance.
	 * 
	 * @param data The DFML data to parse.
	 * @return std::shared_ptr<Parser> Shared pointer to the new Parser instance.
	 */
	static std::shared_ptr<Parser> create(const std::string data);

	/**
	 * @brief Parses the DFML data and returns a list of parsed Element objects.
	 * 
	 * @return std::list<std::shared_ptr<Element>> The list of parsed Element objects.
	 */
	std::list<std::shared_ptr<Element>> parse();

private:
	/**
	 * @brief Parses the children of a Node.
	 * 
	 * @param childs The list to store the parsed child elements.
	 */
	void parse_children(std::list<std::shared_ptr<Element>> &childs);

	/**
	 * @brief Parses a Node element.
	 * 
	 * @return std::shared_ptr<Element> The parsed Node element.
	 */
	std::shared_ptr<Element> parse_node();

	/**
	 * @brief Parses the name of a Node element.
	 * 
	 * @return const std::string The parsed name of the Node element.
	 */
	const std::string parse_node_name();

	/**
	 * @brief Parses a string Data element.
	 * 
	 * @return std::shared_ptr<Data> The parsed string Data element.
	 */
	std::shared_ptr<dfml::Data> parse_string();

	/**
	 * @brief Parses a number Data element.
	 * 
	 * @return std::shared_ptr<Data> The parsed number Data element.
	 */
	std::shared_ptr<dfml::Data> parse_number();

	/**
	 * @brief Parses a boolean Data element.
	 * 
	 * @return std::shared_ptr<Data> The parsed boolean Data element.
	 */
	std::shared_ptr<dfml::Data> parse_boolean();

	/**
	 * @brief Checks if the provided character represents a number.
	 * 
	 * @param ch The ASCII value of the character to check.
	 * @return const bool True if the character represents a number, false otherwise.
	 */
	const bool is_number(int ch) const;

	CharIterator i; /**< Iterator for characters used during parsing. */
};

} // namespace dfml
