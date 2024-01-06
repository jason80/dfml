#include <dfml_node.h>

namespace dfml {
	
void Node::add_child(std::shared_ptr<Element> element) {
	children.push_back(element);
}

}
