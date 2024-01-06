#pragma once

#include <string>
#include <memory>

namespace dfml {

class Node;

class CharIterator {
public:
	CharIterator() = default;

	void set_data(const std::string data) { this->data = data; }

	int next();

private:
	std::string data;
	unsigned long i{};
};

class Parser {
public:
	Parser(const std::string data);
	static std::shared_ptr<Parser> create(const std::string data);

	std::shared_ptr<Node> parse();

private:
	CharIterator i{};
};

}
