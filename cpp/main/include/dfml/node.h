/**
 * @file node.h
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @brief Definition of the Node class in the context of the Dragonfly Markup Language (DFML).
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string>
#include <list>
#include <vector>
#include <dfml/element.h>

namespace dfml {

class Value;

/**
 * @brief Class representing a node in the Dragonfly Markup Language (DFML).
 * 
 * This class inherits from the base class Element and provides functionalities for the manipulation
 * and management of nodes in the DFML data structure.
 */
class Node : public Element {
public:
	/**
	 * @brief Default constructor for the Node class.
	 */
	Node() = default;

	/**
	 * @brief Creates and returns a shared pointer to an instance of Node with the specified name.
	 * 
	 * @param name The name of the node.
	 * @return std::shared_ptr<Node> Shared pointer to the new instance of Node.
	 */
	static std::shared_ptr<Node> create(const std::string name);

	/**
	 * @brief Sets the name of the node.
	 * 
	 * @param name The name to set for the node.
	 */
	void set_name(const std::string name) { this->name = name; }

	/**
	 * @brief Gets the name of the node.
	 * 
	 * @return std::string The name of the node.
	 */
	std::string get_name() { return name; }

	/**
	 * @brief Returns the element type as an integer, identifying it as a node.
	 * 
	 * @return int The element type (NODE).
	 */
	int get_element_type() override { return Element::NODE; }

	/**
	 * @brief Adds a child element to the node.
	 * 
	 * @param element The child element to add.
	 */
	void add_child(std::shared_ptr<Element> element);

	/**
	 * @brief Gets the list of child elements of the node.
	 * 
	 * @return const std::list<std::shared_ptr<Element>> List of child elements.
	 */
	const std::list<std::shared_ptr<Element>> get_children() const { return children; }

	/**
	 * @brief Sets an attribute for the node with the given value.
	 * 
	 * @param name The name of the attribute.
	 * @param value The value of the attribute.
	 */
	void set_attribute(const std::string name, const Value value);

	/**
	 * @brief Sets a string attribute for the node.
	 * 
	 * @param name The name of the attribute.
	 * @param value The value of the attribute as a string.
	 */
	void set_attr_string(const std::string name, const std::string value);

	/**
	 * @brief Sets an integer attribute for the node.
	 * 
	 * @param name The name of the attribute.
	 * @param value The value of the attribute as an integer.
	 */
	void set_attr_integer(const std::string name, long value);

	/**
	 * @brief Sets a double attribute for the node.
	 * 
	 * @param name The name of the attribute.
	 * @param value The value of the attribute as a double.
	 */
	void set_attr_double(const std::string name, double value);

	/**
	 * @brief Sets a boolean attribute for the node.
	 * 
	 * @param name The name of the attribute.
	 * @param value The value of the attribute as a boolean.
	 */
	void set_attr_boolean(const std::string name, bool value);

	/**
	 * @brief Gets the value of an attribute given its name.
	 * 
	 * @param name The name of the attribute.
	 * @return const Value* Constant pointer to the attribute's value.
	 */
	Value *get_attr(const std::string name);

	/**
	 * @brief Checks if the node has an attribute given its name.
	 * 
	 * @param name The name of the attribute.
	 * @return true If the node has the attribute.
	 * @return false If the node does not have the attribute.
	 */
	bool has_attr(const std::string name);

	/**
	 * @brief Gets the list of attributes of the node.
	 * 
	 * @return const std::vector<std::pair<std::string, Value>>& List of attributes.
	 */
	const std::vector<std::pair<std::string, Value>> &get_attributes();

private:
	std::string name{}; /**< Name of the node. */
	std::vector<std::pair<std::string, Value>> attrs; /**< List of attributes of the node. */
	std::list<std::shared_ptr<Element>> children; /**< List of child elements of the node. */

};

} // namespace dfml
