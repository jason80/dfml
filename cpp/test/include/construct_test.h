#pragma once

#include <doctest.h>

#include <dfml.h>

#include <string>
#include <sstream>

TEST_CASE("Node name") {
	auto node = dfml::Node::create("test_node");
	CHECK_EQ(node->get_string(), "test_node");
}

TEST_CASE("Node childs") {
	std::stringstream ss;

	ss << "test_node {\n" << "\t" << "child1\n";
	ss << "\t" << "child2\n";
	ss << "}";

	auto node = dfml::Node::create("test_node");
	node->add_child(dfml::Node::create("child1"));
	node->add_child(dfml::Node::create("child2"));

	CHECK_EQ(node->get_string(), ss.str());
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

	CHECK_EQ(node->get_string(), ss.str());
}

TEST_CASE("Data elements") {
	auto data = dfml::Data::create_string("hello");
	CHECK_EQ(data->get_string(), "\"hello\"");
	data = dfml::Data::create_integer(20);
	CHECK_EQ(data->get_string(), "20");
	data = dfml::Data::create_double(3.14);
	CHECK_EQ(data->get_string(), "3.14");
	data = dfml::Data::create_boolean(true);
	CHECK_EQ(data->get_string(), "true");
}
