#pragma once

#include <memory>
#include <string>

namespace dfml {

class Node;
class Element;
class Data;
class Value;

class Builder {
public:
	static std::shared_ptr<Builder> create();
	const std::string build_node(const std::shared_ptr<Node> node);
	const std::string build_element(const std::shared_ptr<Element> element);
	const std::string build_data(const std::shared_ptr<Data> data) const;
	const std::string build_value(Value value) const;
	const std::string build_attributes(const std::shared_ptr<Node> node);

private:

	const std::string indent() const;

	unsigned level{};
};

}
