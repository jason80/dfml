/**
 * @file comment.h
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @brief Declaration of the Comment class in the context of the Dragonfly Markup Language (DFML).
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <dfml/element.h>

#include <memory>

namespace dfml {

/**
 * @brief Class representing a comment element in the Dragonfly Markup Language (DFML).
 */
class Comment : public Element {
public:
	/**
	 * @brief Creates and returns a shared pointer to an empty Comment instance.
	 * 
	 * @return std::shared_ptr<Comment> Shared pointer to the new Comment instance.
	 */
	static std::shared_ptr<Comment> create();

	/**
	 * @brief Creates and returns a shared pointer to a Comment instance with the specified string content.
	 * 
	 * @param string The content of the comment.
	 * @return std::shared_ptr<Comment> Shared pointer to the new Comment instance.
	 */
	static std::shared_ptr<Comment> create(const std::string string);

	/**
	 * @brief Sets the string content of the comment.
	 * 
	 * @param string The content to set for the comment.
	 */
	void set_string(const std::string string) { this->string = string; }

	/**
	 * @brief Gets the string content of the comment.
	 * 
	 * @return const std::string The content of the comment.
	 */
	const std::string get_string() const { return string; }

	/**
	 * @brief Gets the element type as an integer, identifying it as a comment.
	 * 
	 * @return int The element type (COMMENT).
	 */
	int get_element_type() override { return Element::COMMENT; }

private:
	std::string string{}; /**< Content of the comment. */
};

} // namespace dfml
