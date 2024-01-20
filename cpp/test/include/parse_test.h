#pragma once

#include <doctest.h>
#include <string>
//#include <sstream>

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
		std::string string = "test   {     test1     test2   {  test3  }  }  ";
		auto parser = dfml::Parser::create(string);
		auto list = parser->parse();

		CHECK(list.size() == 1);

		CHECK(list.front()->get_element_type() == dfml::Element::NODE);
		auto test = std::static_pointer_cast<dfml::Node>(list.front());
		CHECK_EQ(test->get_name(), "test");

		CHECK(test->get_children().size() == 2);

		CHECK(test->get_children().front()->get_element_type() == dfml::Element::NODE);
		CHECK(test->get_children().back()->get_element_type() == dfml::Element::NODE);

		auto test1 = std::static_pointer_cast<dfml::Node>(test->get_children().front());
		CHECK_EQ(test1->get_name(), "test1");
		auto test2 = std::static_pointer_cast<dfml::Node>(test->get_children().back());
		CHECK_EQ(test2->get_name(), "test2");

		CHECK(test1->get_children().size() == 0);
		CHECK(test2->get_children().size() == 1);

		auto test3 = std::static_pointer_cast<dfml::Node>(test2->get_children().front());
		CHECK_EQ(test3->get_name(), "test3");
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
}
