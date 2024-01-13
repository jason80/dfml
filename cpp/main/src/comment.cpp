#include <dfml/comment.h>

namespace dfml {

std::shared_ptr<Comment> Comment::create() {
	return std::make_shared<Comment>();
}

std::shared_ptr<Comment> Comment::create(const std::string string) {
	auto comment = create();
	comment->set_string(string);
	return comment;
}

}
