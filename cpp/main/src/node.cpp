#include <dfml/node.h>

#include <sstream>

#include <dfml/value.h>

namespace dfml {

std::shared_ptr<Node> Node::create(const std::string name) {
	auto node = std::make_shared<Node>();
	node->set_name(name);
	return node;
}

void Node::add_child(std::shared_ptr<Element> element) {
	children.push_back(element);
}

void Node::set_attr_string(const std::string name, const std::string value) {
	auto val = Value();
	val.set_string(value);
	attrs.push_back(std::make_pair(name, val));
}

void Node::set_attr_integer(const std::string name, long value) {
	auto val = Value();
	val.set_integer(value);
	attrs.push_back(std::make_pair(name, val));
}

void Node::set_attr_double(const std::string name, double value) {
	auto val = Value();
	val.set_double(value);
	attrs.push_back(std::make_pair(name, val));
}

void Node::set_attr_boolean(const std::string name, bool value) {
	auto val = Value();
	val.set_boolean(value);
	attrs.push_back(std::make_pair(name, val));
}


const Value *Node::get_attr(const std::string name) {
	for (auto &p : attrs) {
		if (p.first == name) return &p.second;
	}

	return nullptr;
}

bool Node::has_attr(const std::string name) {
	for (auto &p : attrs) {
		if (p.first == name) return true;
	}

	return false;
}

const std::vector<std::pair<std::string, Value>> &Node::get_attributes() {
	return attrs;
}

}
