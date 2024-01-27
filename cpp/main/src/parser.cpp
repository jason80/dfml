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
#include <dfml/comment.h>

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
	dfml::Value value;
	while ((ch = i.next()) != -1) {
		switch (ch) {
		case ' ':
		case '\t':
		case '\n':
			break; // space (continue)

		case '/':
		case '#':
			i.back();
			childs.push_back(parse_comment());
			break;

		case '"':
		case '\'':
			parse_string(value);
			childs.push_back(dfml::Data::create(value));
			break;
		
		// End of parsing chidren
		case '}': return ;
		
		default:
			if (std::isalpha(ch)) {
				i.back();
				childs.push_back(parse_node());
			} else if (std::isdigit(ch)) {
				i.back();
				parse_number(value);
				childs.push_back(dfml::Data::create(value));
			} else {
				throw ParserException("Invalid character for node child on line: " +
						i.get_line());
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
		throw ParserException("Empty node name encountered on line: " + i.get_line());
	}

	// Parse attributes and children
	bool stop = false, attr_parsed = false;
	while ((ch = i.next()) != -1) {
		switch (ch) {
		case ' ':
		case '\t':
		case '\n':
			break; // space (continue)

		case '(':
			if (attr_parsed) {
				throw ParserException("Double attribute list found in the node on line: " +
						i.get_line());
			}
			parse_node_attributes(node);
			attr_parsed = true;
			break;

		case '{':
			parse_children(children);
			stop = true;
			break;

		case '}':
			stop = true;
			break;
		default:
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
 * @brief Parse attibutes for the given node.
 * @param node The node reference.
 * 
 */
void Parser::parse_node_attributes(std::shared_ptr<Node> node) {
	int ch;
	bool stop = false;
	
	while ((ch = i.next()) != -1 && !stop) {
		switch (ch) {
		case ' ':
		case '\n':
		case '\t':
		case '\r':

		case ',': // TODO: Improve ',' separator
			// Continue
			break;

		case ')':
			stop = true;
			break;
		}

		if (std::isalpha(ch)) {
			i.back();
			parse_node_attribute(node);
		}

		if (stop) break;
	}
}

/**
 * @brief Parse a attribute pair (Key/Value) for the given node.
 * @param node The node reference
 */
void Parser::parse_node_attribute(std::shared_ptr<Node> node) {
	int ch;
	bool stop = false;
	std::string key;
	Value value;

	enum status_t {
		PARSING_NAME,
		FIND_SEP,
		FIND_VALUE
	} status = PARSING_NAME;

	// Parse key
	while ((ch = i.next()) != -1 && !stop) {
		switch (status) {
		case FIND_VALUE:

			switch (ch) {

			case ' ':
			case '\n':
			case '\t':
			case '\r':
				// Continue
				break;

			case '"':
			case '\'':
				parse_string(value);
				node->set_attribute(key, value);
				return ;
			
			/*default:
				// Error
				break;*/
			}

			if (is_number(ch)) {
				i.back();
				parse_number(value);
				node->set_attribute(key, value);
				i.back();
				return;
			}
			if (std::isalpha(ch)) {
				i.back();
				parse_boolean(value);
				node->set_attribute(key, value);
				i.back();
				return;
			}

			break;
		case FIND_SEP:
			switch (ch) {
			case ' ':
			case '\n':
			case '\t':
			case '\r':
				// Continue
				break;

			case ':':
				status = FIND_VALUE;
				break;
			case ',':
			case ')':
				// Empty attribute
				node->set_attr_string(key, "");
				return;
			}
			break;

		case PARSING_NAME:
			switch (ch) {

			case ' ':
			case '\n':
			case '\t':
			case '\r':
			case ':':
				status = FIND_SEP;
				i.back();
				break;

			case ',':
			case ')':
				// Empty attribute
				node->set_attr_string(key, "");
				return;

			/*default:
				// Error
				return;*/
			}


			if (std::isalnum(ch) || ch == '_') {
				key += ch;
			}
			break;
		}
	}
}

/**
 * @brief Parses a string element in the DFML data.
 * @param value Value reference to set string data.
 */
void Parser::parse_string(dfml::Value &value) {
	std::string result;
	int ch;

	int end = i.current();

	while ((ch = i.next()) != -1) {
		if (ch == end) break;
		result += ch;
	}
	
	value.set_string(result);
}

/**
 * @brief Parses a number Data element.
 * Detect float point to se double data or se fixed to integer.
 * @param value Value reference to set number data.
 */
void Parser::parse_number(dfml::Value &value) {
	int ch;
	std::string result;
	double dbl_result = 0.0;
	long int_result = 0;
	bool dbl = false;
	size_t pos;
	bool error = false;

	while ((ch = i.next()) != -1) {
		if (!is_number(ch)) break;
		if (ch == '.') dbl = true;
		result += ch;
	}

	if (dbl) {
		try {
			dbl_result = std::stod(result, &pos);
			if (pos != result.length()) {
				error = true;
			}
		} catch( ... ) {
			error = true;
		}

		if (error) throw ParserException("Double conversion error on line: " + i.get_line());

		value.set_double(dbl_result);
	} else {
		try {
			int_result = std::stol(result, &pos);
			if (pos != result.length()) {
				error = true;
			}
		} catch( ... ) {
			error = true;
		}

		if (error) throw ParserException("Integer conversion error on line: " + i.get_line());

		value.set_integer(int_result);
	}
}

/**
 * @brief Parses a boolean Data element.
 * @param value Value reference to set boolean data.
 */
void Parser::parse_boolean(Value &value) {
	int ch;
	std::string result;
	while ((ch = i.next()) != -1) {
		if (!std::isalpha(ch)) break;
		result += ch;
	}

	if (result == "true" || result == "false") {
		value.set_boolean(result == "true" ? true : false);
	} else {
		throw ParserException("Boolean conversion error on line: " + i.get_line());
	}
}

/**
 * @brief Parses a Comment element.
 * Parses //, /* and # comment type.
 * 
 * @return std::shared_ptr<Element> The parsed Comment element.
 */
std::shared_ptr<Element> Parser::parse_comment() {
	int ch = i.next();
	bool single_line = false;
	std::string string;

	if (ch == '#') single_line = true;
	else if (ch == '/') {
		ch = i.next();
		if (ch == -1) {
			throw ParserException("Unexpected comment termination on line: " + i.get_line());
		} else if (ch == '/') {
			single_line = true;
		}
		else if (ch == '*') {single_line = false;}
		else {
			throw ParserException("Unexpected comment termination on line: " + i.get_line());
		}
	}

	bool stop = false;
	while ((ch = i.next()) != -1 && !stop) {
		switch(ch) {

		case '\r':
			if (!single_line) string += ch;
			// Continue
			break;

		case '\n':
			if (single_line) {
				i.back();
				stop = true;
			}
			else string += ch;
			break;

		case '*':
			if (!single_line) {
				ch = i.next();
				if (ch == '/' || ch == -1) {
					stop = true;
				} else {
					string += ch;
				}
			} else string += ch;
			break;

		default:
			string += ch;
		}
	}

	return dfml::Comment::create(string);
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
	if (ch == '\n') line ++;
	return ch;
}

/**
 * @brief Moves the iterator back by one character.
 */
void CharIterator::back() {
	i --;
}

}  // namespace dfml
