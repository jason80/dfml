#pragma once

#include <doctest.h>
#include <string>

#include <dfml/parser.h>
#include <dfml/dfml.h>

TEST_SUITE("Parser") {
	TEST_CASE("Single node") {
		std::string test = "test";
		auto parser = dfml::Parser::create(test);
		auto list = parser->parse();

		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Element::NODE);
		CHECK_EQ(std::static_pointer_cast<dfml::Node>(list.front())->get_name(), "test");
	}

	TEST_CASE("Child nodes") {
		std::string string = "red   {     green     blue   {  yellow  }  }  ";
		auto parser = dfml::Parser::create(string);
		auto list = parser->parse();

		CHECK(list.size() == 1);

		CHECK(list.front()->get_element_type() == dfml::Element::NODE);
		auto test = std::static_pointer_cast<dfml::Node>(list.front());
		CHECK_EQ(test->get_name(), "red");

		CHECK(test->get_children().size() == 2);

		CHECK(test->get_children().front()->get_element_type() == dfml::Element::NODE);
		CHECK(test->get_children().back()->get_element_type() == dfml::Element::NODE);

		auto test1 = std::static_pointer_cast<dfml::Node>(test->get_children().front());
		CHECK_EQ(test1->get_name(), "green");
		auto test2 = std::static_pointer_cast<dfml::Node>(test->get_children().back());
		CHECK_EQ(test2->get_name(), "blue");

		CHECK(test1->get_children().size() == 0);
		CHECK(test2->get_children().size() == 1);

		auto test3 = std::static_pointer_cast<dfml::Node>(test2->get_children().front());
		CHECK_EQ(test3->get_name(), "yellow");
	}

	TEST_CASE("Parse data") {
		std::string string = "'hello' \"HELLO\" 23 5.67, true";

		auto parser = dfml::Parser::create(string);
		auto list = parser->parse();

		CHECK(list.size() == 5);

		std::list<std::shared_ptr<dfml::Element>>::iterator iter;
		iter = list.begin();

		CHECK((*iter)->get_element_type() == dfml::Element::DATA);
		auto data = std::static_pointer_cast<dfml::Data>(*iter);
		CHECK(data->get_value().get_type() == dfml::Value::STRING);
		CHECK_EQ(data->get_value().get_value(), "hello");

		iter ++;

		CHECK((*iter)->get_element_type() == dfml::Element::DATA);
		data = std::static_pointer_cast<dfml::Data>(*iter);
		CHECK(data->get_value().get_type() == dfml::Value::STRING);
		CHECK_EQ(data->get_value().get_value(), "HELLO");

		iter ++;

		CHECK((*iter)->get_element_type() == dfml::Element::DATA);
		data = std::static_pointer_cast<dfml::Data>(*iter);
		CHECK(data->get_value().get_type() == dfml::Value::INTEGER);
		CHECK_EQ(data->get_value().get_value(), "23");

		iter ++;

		CHECK((*iter)->get_element_type() == dfml::Element::DATA);
		data = std::static_pointer_cast<dfml::Data>(*iter);
		CHECK(data->get_value().get_type() == dfml::Value::DOUBLE);
		CHECK_EQ(data->get_value().get_value(), "5.67");

		iter ++;
		CHECK((*iter)->get_element_type() == dfml::Element::DATA);
		data = std::static_pointer_cast<dfml::Data>(*iter);
		CHECK(data->get_value().get_type() == dfml::Value::BOOLEAN);
		CHECK_EQ(data->get_value().get_value(), "true");
	}

	TEST_CASE("Single string value") {
		auto parser = dfml::Parser::create("'single string'");
		auto list = parser->parse();

		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Element::DATA);
		auto data = std::static_pointer_cast<dfml::Data>(list.front());
		CHECK(data->get_value().get_type() == dfml::Value::STRING);
		CHECK_EQ(data->get_value().get_value(), "single string");
	}

	TEST_CASE("Single integer value") {
		auto parser = dfml::Parser::create("1234");
		auto list = parser->parse();

		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Element::DATA);
		auto data = std::static_pointer_cast<dfml::Data>(list.front());
		CHECK(data->get_value().get_type() == dfml::Value::INTEGER);
		CHECK_EQ(data->get_value().get_value(), "1234");
	}

	TEST_CASE("Single double value") {
		auto parser = dfml::Parser::create("1234.46");
		auto list = parser->parse();

		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Element::DATA);
		auto data = std::static_pointer_cast<dfml::Data>(list.front());
		CHECK(data->get_value().get_type() == dfml::Value::DOUBLE);
		CHECK_EQ(data->get_value().get_value(), "1234.46");
	}

	TEST_CASE("Single boolean value") {
		auto parser = dfml::Parser::create("false");
		auto list = parser->parse();

		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Element::DATA);
		auto data = std::static_pointer_cast<dfml::Data>(list.front());
		CHECK(data->get_value().get_type() == dfml::Value::BOOLEAN);
		CHECK_EQ(data->get_value().get_value(), "false");
	}

	TEST_CASE("Attributes: parse empty") {
		auto parser = dfml::Parser::create("mynode()");
		auto list = parser->parse();
		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Data::NODE);
		auto node = std::static_pointer_cast<dfml::Node>(list.front());
		CHECK_EQ(node->get_name(), "mynode");
		CHECK(node->get_attributes().size() == 0);
	}

	TEST_CASE("Attributes: parse single") {
		auto parser = dfml::Parser::create("mynode(test: 'hello')");
		auto list = parser->parse();
		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Data::NODE);
		auto node = std::static_pointer_cast<dfml::Node>(list.front());
		CHECK_EQ(node->get_name(), "mynode");
		CHECK(node->get_attributes().size() == 1);
		CHECK(node->has_attr("test"));
		CHECK_EQ(node->get_attr("test")->get_value(), "hello");
	}

	TEST_CASE("Attributes: parse combined") {
		auto parser = dfml::Parser::create(
			"mynode(test: 'hello', number: 40, boolean: false)");
		auto list = parser->parse();
		CHECK(list.size() == 1);
		CHECK(list.front()->get_element_type() == dfml::Data::NODE);
		auto node = std::static_pointer_cast<dfml::Node>(list.front());
		CHECK_EQ(node->get_name(), "mynode");
		CHECK(node->get_attributes().size() == 3);

		CHECK(node->get_attr("test")->get_type() == dfml::Value::STRING);
		CHECK_EQ(node->get_attr("test")->get_value(), "hello");

		CHECK(node->get_attr("number")->get_type() == dfml::Value::INTEGER);
		CHECK_EQ(node->get_attr("number")->get_value(), "40");

		CHECK(node->get_attr("boolean")->get_type() == dfml::Value::BOOLEAN);
		CHECK_EQ(node->get_attr("boolean")->get_value(), "false");
	}

	TEST_CASE("Comments: single") {
		auto parser = dfml::Parser::create(
			"/*Hello\nWorld*/\n#Single comment\n//Another single");

		auto list = parser->parse();
		CHECK(list.size() == 3);

		auto iter = list.begin();
		CHECK((*iter)->get_element_type() == dfml::Element::COMMENT);
		CHECK_EQ(std::static_pointer_cast<dfml::Comment>(*iter)->get_string(), "Hello\nWorld");
		iter ++;
		CHECK((*iter)->get_element_type() == dfml::Element::COMMENT);
		CHECK_EQ(std::static_pointer_cast<dfml::Comment>(*iter)->get_string(), "Single comment");
		iter ++;
		CHECK((*iter)->get_element_type() == dfml::Element::COMMENT);
		CHECK_EQ(std::static_pointer_cast<dfml::Comment>(*iter)->get_string(), "Another single");
	}
}
