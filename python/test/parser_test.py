from unittest import TestCase
import dfml

class ParserTest(TestCase):
	def test_single_node(self):
		parser = dfml.Parser.create("test");
		list = parser.parse()

		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Element.NODE)
		self.assertEqual(list[0].get_name(), "test")

	def test_child_nodes(self):
		string = "red   {     green     blue   {  yellow  }  }  "
		parser = dfml.Parser.create(string)
		lst = parser.parse()

		self.assertEqual(len(lst), 1)

		self.assertEqual(lst[0].get_element_type(), dfml.Element.NODE)
		test = lst[0]
		self.assertEqual(test.get_name(), "red")

		self.assertEqual(len(test.get_children()), 2)

		self.assertEqual(test.get_children()[0].get_element_type(), dfml.Element.NODE)
		self.assertEqual(test.get_children()[1].get_element_type(), dfml.Element.NODE)

		test1 = test.get_children()[0]
		self.assertEqual(test1.get_name(), "green")
		test2 = test.get_children()[1]
		self.assertEqual(test2.get_name(), "blue")

		self.assertEqual(len(test1.get_children()), 0)
		self.assertEqual(len(test2.get_children()), 1)

		test3 = test2.get_children()[0]
		self.assertEqual(test3.get_name(), "yellow")

	def test_parse_data(self):
		string = "'hello' \"HELLO\" 23 5.67, true"

		parser = dfml.Parser.create(string)
		list = parser.parse()

		self.assertEqual(len(list), 5)

		self.assertEqual(list[0].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[0].get_value().get_type(), dfml.Value.STRING)
		self.assertEqual(list[0].get_value().get_value(), "hello")

		self.assertEqual(list[1].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[1].get_value().get_type(), dfml.Value.STRING)
		self.assertEqual(list[1].get_value().get_value(), "HELLO")

		self.assertEqual(list[2].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[2].get_value().get_type(), dfml.Value.INTEGER)
		self.assertEqual(list[2].get_value().get_value(), "23")

		self.assertEqual(list[3].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[3].get_value().get_type(), dfml.Value.DOUBLE)
		self.assertEqual(list[3].get_value().get_value(), "5.67")

		self.assertEqual(list[4].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[4].get_value().get_type(), dfml.Value.BOOLEAN)
		self.assertEqual(list[4].get_value().get_value(), "true")
		
	def test_single_string_value(self):
		parser = dfml.Parser.create("'single string'")
		list = parser.parse()

		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[0].get_value().get_type(), dfml.Value.STRING)
		self.assertEqual(list[0].get_value().get_value(), "single string")
	
	def test_single_integer_value(self):
		parser = dfml.Parser.create("1234")
		list = parser.parse()

		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[0].get_value().get_type(), dfml.Value.INTEGER)
		self.assertEqual(list[0].get_value().get_value(), "1234")

	def test_single_double_value(self):
		parser = dfml.Parser.create("1234.46")
		list = parser.parse()

		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[0].get_value().get_type(), dfml.Value.DOUBLE)
		self.assertEqual(list[0].get_value().get_value(), "1234.46")

	def test_single_boolean_value(self):
		parser = dfml.Parser.create("false")
		list = parser.parse()

		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Element.DATA)
		self.assertEqual(list[0].get_value().get_type(), dfml.Value.BOOLEAN)
		self.assertEqual(list[0].get_value().get_value(), "false")

	def test_attributes_parse_empty(self):
		parser = dfml.Parser.create("mynode()")
		list = parser.parse()
		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Data.NODE)
		node = list[0]
		self.assertEqual(node.get_name(), "mynode")
		self.assertEqual(len(node.get_attr_keys()), 0)

	def test_attributes_parse_single(self):
		parser = dfml.Parser.create("mynode(test: 'hello')")
		list = parser.parse()
		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Data.NODE)
		node = list[0]
		self.assertEqual(node.get_name(), "mynode")
		self.assertEqual(len(node.get_attr_keys()), 1)
		self.assertTrue(node.has_attr("test"))
		self.assertEqual(node.get_attr("test").get_value(), "hello")

	def test_attributes_parse_combined(self):
		parser = dfml.Parser.create(
			"mynode(test: 'hello', number: 40, boolean: false)")
		list = parser.parse()
		self.assertEqual(len(list), 1)
		self.assertEqual(list[0].get_element_type(), dfml.Data.NODE)
		node = list[0]
		self.assertEqual(node.get_name(), "mynode")
		self.assertEqual(len(node.get_attr_keys()), 3)

		self.assertEqual(node.get_attr("test").get_type(), dfml.Value.STRING)
		self.assertEqual(node.get_attr("test").get_value(), "hello")

		self.assertEqual(node.get_attr("number").get_type(), dfml.Value.INTEGER)
		self.assertEqual(node.get_attr("number").get_value(), "40")

		self.assertEqual(node.get_attr("boolean").get_type(), dfml.Value.BOOLEAN)
		self.assertEqual(node.get_attr("boolean").get_value(), "false")

	def test_comments_single(self):
		parser = dfml.Parser.create(
			"/*Hello\nWorld*/\n#Single comment\n//Another single")

		list = parser.parse()
		self.assertEqual(len(list), 3)

		self.assertEqual(list[0].get_element_type(), dfml.Element.COMMENT)
		self.assertEqual(list[0].get_string(), "Hello\nWorld")

		self.assertEqual(list[1].get_element_type(), dfml.Element.COMMENT)
		self.assertEqual(list[1].get_string(), "Single comment")
	
		self.assertEqual(list[2].get_element_type(), dfml.Element.COMMENT)
		self.assertEqual(list[2].get_string(), "Another single")
