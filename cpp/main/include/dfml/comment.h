#pragma once

#include <dfml/element.h>

#include <memory>

namespace dfml {

class Comment: public Element {
public:
	static std::shared_ptr<Comment> create();
	static std::shared_ptr<Comment> create(const std::string string);

	void set_string(const std::string string) { this->string = string; }
	const std::string get_string() const { return string; }

	int get_element_type() { return Element::COMMENT; }

private:
	std::string string{};
};

}
