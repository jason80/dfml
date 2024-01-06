#pragma once

#include <doctest.h>

#include <dfml.h>

#include <string>

TEST_CASE("Node name") {
	auto node = dfml::Node::create("test_node");
	CHECK_EQ(node->get_string(), "test_node");
}
