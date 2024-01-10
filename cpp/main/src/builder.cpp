#include <dfml/builder.h>

#include <sstream>

#include <dfml/element.h>
#include <dfml/node.h>
#include <dfml/data.h>
#include <dfml/value.h>

namespace dfml {

std::shared_ptr<Builder> Builder::create() {
	return std::make_shared<Builder>();
}

const std::string Builder::build_node(const std::shared_ptr<Node> node) {
	std::stringstream ss;
	ss << indent() << node->get_name();

	if (!node->get_attributes().empty())
		ss << build_attributes(node);

	// Construct childs:
	auto children = node->get_children();
	if (!children.empty()) {
		ss << " {\n"; level ++;
		for (auto &e : children) {
			ss << build_element(e) << "\n";
		}
		level --;
		ss << indent() << "}";
	}
	return ss.str();
}

const std::string Builder::build_element(const std::shared_ptr<Element> element) {
	if (element->get_element_type() == Element::NODE)
		return build_node(std::static_pointer_cast<Node>(element));
	else return build_data(std::static_pointer_cast<Data>(element));
}

const std::string Builder::build_data(const std::shared_ptr<Data> data) const {
	return indent() + build_value(data->get_value());
}

const std::string Builder::build_value(Value value) const {
	if (value.get_type() == Value::STRING) {
		return "\"" + value.get_value() + "\"";
	} else return value.get_value();
}

const std::string Builder::build_attributes(const std::shared_ptr<Node> node) {
	std::stringstream ss;
	std::string sep = "";

	ss << "(";
	for (auto &e : node->get_attributes()) {
		ss << sep; sep = ", ";
		ss << e.first << ": " << build_value(e.second);
	}
	ss << ")";

	return ss.str();
}

const std::string Builder::indent() const {
	if (!level) return "";
	std::stringstream ss;

	for (int i = 0; i < level; i ++) {
		ss << "\t";
	}

	return ss.str();
}

}
