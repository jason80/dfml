#pragma once

#include <string>
#include <list>
#include <dfml/element.h>

namespace dfml {

class Node: public Element {
public:
	Node() = default;
	
	static std::shared_ptr<Node> create(const std::string name);

	void set_name(const std::string name) { this->name = name; }
	std::string get_name() { return name; }

	int get_element_type() override { return Element::NODE; }

	void add_child(std::shared_ptr<Element> element);
	const std::list<std::shared_ptr<Element>> get_children() const { return children; }

private:
	std::string name{};
	std::list<std::shared_ptr<Element>> children;

};

}
