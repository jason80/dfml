#include <dfml/parser.h>

#include <dfml/node.h>

namespace dfml {

Parser::Parser(const std::string data) {
	i.set_data(data);
}

std::shared_ptr<Parser> Parser::create(const std::string data) {
	return std::make_shared<Parser>(data);
}

std::list<std::shared_ptr<Element>> Parser::parse() {
	std::list<std::shared_ptr<Element>> list;
	int ch;
	while ((ch = i.next()) != -1) {
		
	}

	return list;
}

int CharIterator::next() {
	if (i >= data.size()) return -1;
	int ch = data[i]; i ++;
	return ch;
}

}
