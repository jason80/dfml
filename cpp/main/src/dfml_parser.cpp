#include <dfml_parser.h>

#include <dfml_node.h>

namespace dfml {

Parser::Parser(const std::string data) {
	i.set_data(data);
}

std::shared_ptr<Parser> Parser::create(const std::string data) {
	return std::make_shared<Parser>(data);
}

std::shared_ptr<Node> Parser::parse() {
	auto root = std::make_shared<Node>();
	int ch;
	while ((ch = i.next()) != -1) {
		
	}

	return root;
}

int CharIterator::next() {
	if (i >= data.size()) return -1;
	int ch = data[i]; i ++;
	return ch;
}

}
