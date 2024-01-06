#pragma once

#include <string>
#include <list>
#include <dfml_element.h>

namespace dfml {

class Node: public Element {
public:
	Node() = default;
	
	static std::shared_ptr<Node> create(const std::string name);

	void set_name(const std::string name) { this->name = name; }
	std::string get_name() { return name; }

	int get_element_type() override { return Element::NODE; }
	std::string get_string() override;

	void add_child(std::shared_ptr<Element> element);

private:
	std::string name{};
	std::list<std::shared_ptr<Element>> children;
};

}
