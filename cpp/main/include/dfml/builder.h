/**
 * @file builder.h
 * @brief Declaration of the Builder class in the context of the Dragonfly Markup Language (DFML).
 * @author Javier Candales (javier_candales@yahoo.com.ar)
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
class Element;
class Data;
class Comment;
class Value;

/**
 * @brief Class responsible for building DFML representations as strings.
 */
class Builder {
public:
	/**
	 * @brief Creates and returns a shared pointer to a Builder instance.
	 * 
	 * @return std::shared_ptr<Builder> Shared pointer to the new Builder instance.
	 */
	static std::shared_ptr<Builder> create();

	/**
	 * @brief Builds and returns the DFML representation of a Node.
	 * 
	 * @param node The Node to build.
	 * @return const std::string The DFML representation of the Node.
	 */
	const std::string build_node(const std::shared_ptr<Node> node);

	/**
	 * @brief Builds and returns the DFML representation of an Element.
	 * 
	 * @param element The Element to build.
	 * @return const std::string The DFML representation of the Element.
	 */
	const std::string build_element(const std::shared_ptr<Element> element);

	/**
	 * @brief Builds and returns the DFML representation of a Data.
	 * 
	 * @param data The Data to build.
	 * @return const std::string The DFML representation of the Data.
	 */
	const std::string build_data(const std::shared_ptr<Data> data) const;

	/**
	 * @brief Builds and returns the DFML representation of a Value.
	 * 
	 * @param value The Value to build.
	 * @return const std::string The DFML representation of the Value.
	 */
	const std::string build_value(Value value) const;

	/**
	 * @brief Builds and returns the DFML representation of a Comment.
	 * 
	 * @param comment The Comment to build.
	 * @return const std::string The DFML representation of the Comment.
	 */
	const std::string build_comment(const std::shared_ptr<Comment> comment) const;

	/**
	 * @brief Builds and returns the DFML representation of attributes for a Node.
	 * 
	 * @param node The Node for which to build attributes.
	 * @return const std::string The DFML representation of attributes for the Node.
	 */
	const std::string build_attributes(const std::shared_ptr<Node> node);

private:
	/**
	 * @brief Gets the current indentation based on the builder's level.
	 * 
	 * @return const std::string The current indentation.
	 */
	const std::string indent() const;

	unsigned level{}; /**< Current level of indentation. */
};

} // namespace dfml
