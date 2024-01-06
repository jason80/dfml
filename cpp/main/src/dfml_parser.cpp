#include <dfml_parser.h>

namespace dfml {

Parser::Parser(const std::string data) {

}

std::shared_ptr<Parser> Parser::create(const std::string data) {
	return std::make_shared<Parser>(data);
}

}
