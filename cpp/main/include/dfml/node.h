#pragma once

#include <string>
#include <list>
#include <vector>
#include <dfml/element.h>

namespace dfml {

class Value;

class Node: public Element {
public:
	Node() = default;
	
	static std::shared_ptr<Node> create(const std::string name);

	void set_name(const std::string name) { this->name = name; }
	std::string get_name() { return name; }

	int get_element_type() override { return Element::NODE; }

	void add_child(std::shared_ptr<Element> element);
	const std::list<std::shared_ptr<Element>> get_children() const { return children; }

	void set_attr_string(const std::string name, const std::string value);
	void set_attr_integer(const std::string name, long value);
	void set_attr_double(const std::string name, double value);
	void set_attr_boolean(const std::string name, bool value);

	const Value *get_attr(const std::string name);
	bool has_attr(const std::string name);

	const std::vector<std::pair<std::string, Value>> &get_attributes();

private:
	std::string name{};
	std::vector<std::pair<std::string, Value>> attrs;
	std::list<std::shared_ptr<Element>> children;

};

}
