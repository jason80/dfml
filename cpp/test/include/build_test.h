#pragma once

#include <doctest.h>

#include <dfml/builder.h>
#include <dfml/dfml.h>

#include <string>
#include <sstream>

TEST_SUITE("Builder") {

TEST_CASE("Node name") {
	auto builder = dfml::Builder::create();
	CHECK_EQ(builder->build_node(dfml::Node::create("test_node")), "test_node");
}

TEST_CASE("Node childs") {
	std::stringstream ss;

	ss << "test_node {\n" << "\t" << "child1\n";
	ss << "\t" << "child2\n";
	ss << "\t" << "\"string data\"\n";
	ss << "\t" << 20000 << "\n";
	ss << "\t" << "false\n";
	ss << "\t" << 3.149 << "\n";
	ss << "}";

	auto node = dfml::Node::create("test_node");
	node->add_child(dfml::Node::create("child1"));
	node->add_child(dfml::Node::create("child2"));
	node->add_child(dfml::Data::create_string("string data"));
	node->add_child(dfml::Data::create_integer(20000));
	node->add_child(dfml::Data::create_boolean(false));
	node->add_child(dfml::Data::create_double(3.149));

	auto builder = dfml::Builder::create();

	CHECK_EQ(builder->build_node(node), ss.str());
}

TEST_CASE("Node child's child") {
	std::stringstream ss;

	ss << "test_node {\n" << "\t" << "child1\n";
	ss << "\t" << "child2 {\n";
	ss << "\t\t" << "child3\n";
	ss << "\t}\n";
	ss << "}";

	auto node = dfml::Node::create("test_node");
	auto child = dfml::Node::create("child1"); node->add_child(child);
	child = dfml::Node::create("child2"); node->add_child(child);
	child->add_child(dfml::Node::create("child3"));

	auto builder = dfml::Builder::create();

	CHECK_EQ(builder->build_node(node), ss.str());
}

TEST_CASE("Data elements") {
	auto data = dfml::Data::create_string("hello");
	auto builder = dfml::Builder::create();
	CHECK_EQ(builder->build_data(data), "\"hello\"");
	data = dfml::Data::create_integer(20);
	CHECK_EQ(builder->build_data(data), "20");
	data = dfml::Data::create_double(3.14);
	CHECK_EQ(builder->build_data(data), "3.14");
	data = dfml::Data::create_boolean(true);
	CHECK_EQ(builder->build_data(data), "true");
}

TEST_CASE("Node attributes") {
	auto node = dfml::Node::create("person");
	node->set_attr_string("name", "John");
	node->set_attr_string("last", "Doe");
	node->set_attr_integer("ages", 40);
	node->set_attr_double("height", 1.65);
	node->set_attr_boolean("single", true);

	std::string test =
		"person(name: \"John\", last: \"Doe\", ages: 40, height: 1.65, single: true)";

	auto builder = dfml::Builder::create();
	CHECK_EQ(builder->build_node(node), test);
}

TEST_CASE("Comments") {
	auto node = dfml::Node::create("test_comments");
	node->add_child(dfml::Comment::create("comment 1"));
	node->add_child(dfml::Comment::create("comment 2"));

	std::string test =
	"test_comments {\n\t/*comment 1*/\n\t/*comment 2*/\n}";
	auto builder = dfml::Builder::create();
	CHECK_EQ(builder->build_node(node), test);
}

}
