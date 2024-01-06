#pragma once

#include <string>
#include <memory>

namespace dfml {

class Parser {
public:
	Parser(const std::string data);
	static std::shared_ptr<Parser> create(const std::string data);

private:
	std::string data;
};

}
