#pragma once

#include <string>
#include <memory>
#include <list>

namespace dfml {

class Element;

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

	std::list<std::shared_ptr<Element>> parse();

private:
	CharIterator i{};
};

}
