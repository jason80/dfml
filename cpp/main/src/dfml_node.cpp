#include <dfml_node.h>

#include <sstream>

namespace dfml {

std::shared_ptr<Node> Node::create(const std::string name) {
	auto node = std::make_shared<Node>();
	node->set_name(name);
	return node;
}

std::string Node::construct(int level) {
	std::stringstream ss;
	ss << name;

	// TODO: construct attributes

	// Construct childs:
	if (!children.empty()) {
		ss << " {\n";
		for (auto &e : children) {
			ss << repeat_string(level + 1, "\t") << e->construct(level + 1) << "\n";
		}
		ss << repeat_string(level, "\t") << "}";
	}

	return ss.str();
}

void Node::add_child(std::shared_ptr<Element> element) {
	children.push_back(element);
}

std::string Node::repeat_string(int times, const std::string str) {
	if (!times) return "";
	std::stringstream ss;

	for (int i = 0; i < times; i ++) {
		ss << str;
	}

	return ss.str();
}

}
