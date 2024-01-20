/**
 * @file parser.cpp
 * @brief Implementation of the Parser class for Dragonfly Markup Language (DFML) parsing.
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @date 2024-01-20
 * 
 * @copyright Copyright (c) 2024
 */

#include <dfml/parser.h>
#include <dfml/node.h>
#include <dfml/data.h>

namespace dfml {

/**
 * @brief Constructor for the Parser class.
 * @param data The DFML data to be parsed.
 */
Parser::Parser(const std::string data) {
	i.set_data(data);
}

/**
 * @brief Static factory method to create an instance of the Parser class.
 * @param data The DFML data to be parsed.
 * @return A shared pointer to the created Parser object.
 */
std::shared_ptr<Parser> Parser::create(const std::string data) {
	return std::make_shared<Parser>(data);
}

/**
 * @brief Parses the DFML data and returns a list of shared pointers to parsed elements.
 * @return A list of shared pointers to parsed elements.
 */
std::list<std::shared_ptr<Element>> Parser::parse() {
	std::list<std::shared_ptr<Element>> list;
	
	parse_children(list);

	return list;
}

/**
 * @brief Parses child elements in the DFML data.
 * @param childs Reference to a list to store the parsed child elements.
 */
void Parser::parse_children(std::list<std::shared_ptr<Element>> &childs) {
	int ch;
	while ((ch = i.next()) != -1) {
		switch (ch) {
		case ' ':
		case '\t':
		case '\n':
			break; // space (continue)

		case '/':
		case '#':
			// TODO: parse comment
			break;

		case '"':
		case '\'':
			childs.push_back(parse_string());
			break;
		
		default:
			if (std::isalpha(ch)) {
				i.back();
				childs.push_back(parse_node());
			} else if (std::isdigit(ch)) {
				i.back();
				childs.push_back(parse_number());
			} else {
				// TODO: Invalid character
			}
		}
	}
}

/**
 * @brief Parses a node element in the DFML data.
 * @return A shared pointer to the parsed node element.
 */
std::shared_ptr<Element> Parser::parse_node() {
	int ch;
	std::string name = parse_node_name();

	// If keywords "true" or "false" isn't a node: it is boolean data.
	if (name == "true") {
		return dfml::Data::create_boolean(true);
	} else if (name == "false") {
		return dfml::Data::create_boolean(false);
	}

	// Create a node
	auto node = dfml::Node::create(name);
	std::list<std::shared_ptr<Element>> children;

	if (i.end()) return node;

	i.back();

	if (node->get_name() == "") {
		// TODO: Empty name
	}

	// TODO: Parse attributes

	// Parse children
	bool stop = false;
	while ((ch = i.next()) != -1) {
		switch (ch) {
		case ' ':
		case '\t':
		case '\n':
			break; // space (continue)

		case '{':
			parse_children(children);
			break;
		default:
			// TODO: Invalid character
			stop = true;
			i.back();
			break;
		}

		if (stop) break;
	}

	for (auto &e : children) {
		node->add_child(e);
	}

	return node;
}

/**
 * @brief Parses the name of a node element in the DFML data.
 * @return The name of the parsed node.
 */
const std::string Parser::parse_node_name() {
	int ch;
	std::string name = "";
	while ((ch = i.next()) != -1) {
		if (std::isalnum(ch)) {
			name += ch;
		} else break;
	}
	return name;
}

/**
 * @brief Parses a string element in the DFML data.
 * @return A shared pointer to the parsed string element.
 */
std::shared_ptr<dfml::Data> Parser::parse_string() {
	std::string result;
	int ch;

	int end = i.current();

	while ((ch = i.next()) != -1) {
		if (ch == end) break;
		result += ch;
	}
	
	return dfml::Data::create_string(result);
}

/**
 * @brief Parses a number element in the DFML data.
 * @return A shared pointer to the parsed number element.
 */
std::shared_ptr<dfml::Data> Parser::parse_number() {
	int ch;
	std::string result;
	double dbl_result = 0.0;
	long int_result = 0;
	bool dbl = false;
	size_t pos;

	while ((ch = i.next()) != -1) {
		if (!is_number(ch)) break;
		if (ch == '.') dbl = true;
		result += ch;
	}

	if (dbl) {
		try {
			dbl_result = std::stod(result, &pos);
			if (pos != result.length()) {
				// TODO: Double conversion
			}
		} catch( ... ) {
			// TODO: Double conversion
		}
		return dfml::Data::create_double(dbl_result);
	} else {
		try {
			int_result = std::stol(result, &pos);
			if (pos != result.length()) {
				// TODO: Integer conversion
			}
		} catch( ... ) {
			// TODO: Integer conversion
		}
		return dfml::Data::create_integer(int_result);
	}
}

/**
 * @brief Checks if the given character represents a number.
 * @param ch The character to be checked.
 * @return True if the character represents a number, otherwise false.
 */
const bool Parser::is_number(int ch) const {
	if (std::isdigit(ch)) return true;
	if (ch == '-' || ch == '.') return true;
	return false;
}

/**
 * @brief Gets the next character in the DFML data.
 * @return The ASCII value of the next character, or -1 if end of data is reached.
 */
int CharIterator::next() {
	if (i >= data.size()) return -1;
	int ch = data[i]; i ++;
	return ch;
}

/**
 * @brief Moves the iterator back by one character.
 */
void CharIterator::back() {
	i --;
}

}  // namespace dfml
