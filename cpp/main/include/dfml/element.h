/**
 * @file element.h
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @brief Declaration of the Element class in the context of the Dragonfly Markup Language (DFML).
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <memory>
#include <string>

namespace dfml {

class Node;

/**
 * @brief Base class representing an element in the Dragonfly Markup Language (DFML) structure.
 */
class Element {
public:
	/**
	 * @brief Gets the parent node of the element.
	 * 
	 * @return std::shared_ptr<Node> Shared pointer to the parent node.
	 */
	std::shared_ptr<Node> get_parent() { return parent; }

	/**
	 * @brief Gets the type of the element.
	 * 
	 * @return int The element type.
	 * - NODE: 0 - Represents a node.
	 * - DATA: 1 - Represents a data (value only).
	 * - COMMENT: 2 - Represents a comment.
	 */
	virtual int get_element_type() = 0;

	/**
	 * @brief Constant representing a Node element type.
	 */
	static constexpr int NODE = 0;

	/**
	 * @brief Constant representing a Data.
	 */
	static constexpr int DATA = 1;

	/**
	 * @brief Constant representing a Comment element type.
	 */
	static constexpr int COMMENT = 2;

private:
	std::shared_ptr<Node> parent; /**< Shared pointer to the parent node. */
};

} // namespace dfml
