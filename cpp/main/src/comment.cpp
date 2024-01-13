/**
 * @file comment.cpp
 * @author Javier Candales (javier_candales@yahoo.com.ar)
 * @brief Implementation of the Comment class methods in the context of the Dragonfly Markup Language (DFML).
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dfml/comment.h>

namespace dfml {

/**
 * @brief Creates and returns a shared pointer to an empty Comment instance.
 * 
 * @return std::shared_ptr<Comment> Shared pointer to the new Comment instance.
 */
std::shared_ptr<Comment> Comment::create() {
	return std::make_shared<Comment>();
}

/**
 * @brief Creates and returns a shared pointer to a Comment instance with the specified string content.
 * 
 * @param string The content of the comment.
 * @return std::shared_ptr<Comment> Shared pointer to the new Comment instance.
 */
std::shared_ptr<Comment> Comment::create(const std::string string) {
	auto comment = create();
	comment->set_string(string);
	return comment;
}

} // namespace dfml
