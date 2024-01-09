#pragma once

#include <memory>
#include <string>

namespace dfml {

class Node;

class Element {
public:

	std::shared_ptr<Node> get_parent() { return parent; }
	virtual int get_element_type() = 0;
	virtual std::string construct(int level) = 0;
	std::string get_string() { return construct(0); }

	static constexpr int NODE = 0;
	static constexpr int DATA = 1;

private:
	std::shared_ptr<Node> parent;
};

}
