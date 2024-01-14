/**
 * @file builder.cpp
 * @brief Implementation of the Builder class methods in the context of the Dragonfly Markup Language (DFML).
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dfml/builder.h>

#include <sstream>

#include <dfml/element.h>
#include <dfml/node.h>
#include <dfml/data.h>
#include <dfml/comment.h>
#include <dfml/value.h>

namespace dfml {

/**
 * @brief Constructor of Builder class.
 * 
 */
Builder::Builder() {
	format = true;
	use_spaces = false;
	space_count = 4;
}

/**
 * @brief Creates and returns a shared pointer to a Builder instance.
 * 
 * @return std::shared_ptr<Builder> Shared pointer to the new Builder instance.
 */
std::shared_ptr<Builder> Builder::create() {
	return std::make_shared<Builder>();
}

/**
 * @brief Builds and returns the DFML representation of a Node.
 * 
 * @param node The Node to build.
 * @return const std::string The DFML representation of the Node.
 */
const std::string Builder::build_node(const std::shared_ptr<Node> node) {
	std::stringstream ss;
	ss << indent() << node->get_name();

	if (!node->get_attributes().empty())
		ss << build_attributes(node);

	// Construct children:
	auto children = node->get_children();
	if (!children.empty()) {
		ss << (format ? " {\n" : " { ");
		level++;
		for (auto &e : children) {
			ss << build_element(e) << (format ? "\n" : " ");
		}
		level--;
		ss << indent() << "}";
	}
	return ss.str();
}

/**
 * @brief Builds and returns the DFML representation of an Element.
 * 
 * @param element The Element to build.
 * @return const std::string The DFML representation of the Element.
 */
const std::string Builder::build_element(const std::shared_ptr<Element> element) {
	if (element->get_element_type() == Element::NODE)
		return build_node(std::static_pointer_cast<Node>(element));
	else if (element->get_element_type() == Element::DATA)
		return build_data(std::static_pointer_cast<Data>(element));
	else
		return build_comment(std::static_pointer_cast<Comment>(element));
}

/**
 * @brief Builds and returns the DFML representation of a Data.
 * 
 * @param data The Data to build.
 * @return const std::string The DFML representation of the Data.
 */
const std::string Builder::build_data(const std::shared_ptr<Data> data) const {
	return indent() + build_value(data->get_value());
}

/**
 * @brief Builds and returns the DFML representation of a Comment.
 * 
 * @param comment The Comment to build.
 * @return const std::string The DFML representation of the Comment.
 */
const std::string Builder::build_comment(const std::shared_ptr<Comment> comment) const {
	return indent() + "/*" + comment->get_string() + "*/";
}

/**
 * @brief Builds and returns the DFML representation of a Value.
 * 
 * @param value The Value to build.
 * @return const std::string The DFML representation of the Value.
 */
const std::string Builder::build_value(Value value) const {
	if (value.get_type() == Value::STRING) {
		return "\"" + value.get_value() + "\"";
	} else
		return value.get_value();
}

/**
 * @brief Builds and returns the DFML representation of attributes for a Node.
 * 
 * @param node The Node for which to build attributes.
 * @return const std::string The DFML representation of attributes for the Node.
 */
const std::string Builder::build_attributes(const std::shared_ptr<Node> node) {
	std::stringstream ss;
	std::string sep = "";

	ss << "(";
	for (auto &e : node->get_attributes()) {
		ss << sep;
		sep = ", ";
		ss << e.first << ": " << build_value(e.second);
	}
	ss << ")";

	return ss.str();
}

/**
 * @brief Gets the current indentation based on the builder's level.
 * 
 * @return const std::string The current indentation.
 */
const std::string Builder::indent() const {
	if (!format) return "";
	if (!level) return "";
	std::stringstream ss;
	std::string ind(space_count, ' ');

	for (int i = 0; i < level; i++) {
		if (use_spaces) ss << ind;	
		else ss << "\t";
	}

	return ss.str();
}

} // namespace dfml
