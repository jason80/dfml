/**
 * @file node.cpp
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @brief Implementation of the Node class in the context of the Dragonfly Markup Language (DFML).
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dfml/node.h>

#include <sstream>

#include <dfml/value.h>

namespace dfml {

/**
 * @brief Creates and returns a shared pointer to a Node instance with the specified name.
 * 
 * @param name The name of the node.
 * @return std::shared_ptr<Node> Shared pointer to the new instance of Node.
 */
std::shared_ptr<Node> Node::create(const std::string name) {
	auto node = std::make_shared<Node>();
	node->set_name(name);
	return node;
}

/**
 * @brief Adds a child element to the node.
 * 
 * @param element The child element to add.
 */
void Node::add_child(std::shared_ptr<Element> element) {
	children.push_back(element);
}

/**
 * @brief Sets an attribute for the node with the given value.
 * 
 * @param name The name of the attribute.
 * @param value The value of the attribute.
 */
void Node::set_attribute(const std::string name, const Value value) {
	if (!this->has_attr(name)) keys.push_back(name);
	attrs[name] = value;
}

/**
 * @brief Sets a string attribute for the node.
 * 
 * @param name The name of the attribute.
 * @param value The value of the attribute as a string.
 */
void Node::set_attr_string(const std::string name, const std::string value) {
	auto val = Value();
	val.set_string(value);

	if (!this->has_attr(name)) keys.push_back(name);
	attrs[name] = val;
}

/**
 * @brief Sets an integer attribute for the node.
 * 
 * @param name The name of the attribute.
 * @param value The value of the attribute as an integer.
 */
void Node::set_attr_integer(const std::string name, long value) {
	auto val = Value();
	val.set_integer(value);

	if (!this->has_attr(name)) keys.push_back(name);
	attrs[name] = val;
}

/**
 * @brief Sets a double attribute for the node.
 * 
 * @param name The name of the attribute.
 * @param value The value of the attribute as a double.
 */
void Node::set_attr_double(const std::string name, double value) {
	auto val = Value();
	val.set_double(value);

	if (!this->has_attr(name)) keys.push_back(name);
	attrs[name] = val;
}

/**
 * @brief Sets a boolean attribute for the node.
 * 
 * @param name The name of the attribute.
 * @param value The value of the attribute as a boolean.
 */
void Node::set_attr_boolean(const std::string name, bool value) {
	auto val = Value();
	val.set_boolean(value);

	if (!this->has_attr(name)) keys.push_back(name);
	attrs[name] = val;
}

/**
 * @brief Gets the value of an attribute given its name.
 * 
 * @param name The name of the attribute.
 * @return const Value & Attribute's value reference.
 */
Value &Node::get_attr(const std::string name) {
	return attrs[name];
}

/**
 * @brief Checks if the node has an attribute given its name.
 * 
 * @param name The name of the attribute.
 * @return true If the node has the attribute.
 * @return false If the node does not have the attribute.
 */
bool Node::has_attr(const std::string name) {
	for (auto &k : keys) {
		if (k == name) return true;
	}

	return false;
}

} // namespace dfml
