#include <dfml_node.h>

namespace dfml {

std::shared_ptr<Node> Node::create(const std::string name) {
	auto node = std::make_shared<Node>();
	node->set_name(name);
	return node;
}

std::string Node::get_string() {
	return name;
}

void Node::add_child(std::shared_ptr<Element> element) {
	children.push_back(element);
}

}
