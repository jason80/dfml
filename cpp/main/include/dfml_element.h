#pragma once

#include <memory>

namespace dfml {

class Node;

class Element {
public:

	std::shared_ptr<Node> get_parent() { return parent; }
	virtual int get_element_type() = 0;

	static constexpr int NODE = 0;

private:
	std::shared_ptr<Node> parent;
};

}
