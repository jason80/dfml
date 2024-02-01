from unittest import TestCase
import dfml

class BuildTest(TestCase):
	def test_node_name(self):
		builder = dfml.Builder.create()
		node = dfml.Node.create("hello")
		self.assertEqual(builder.build_node(node), "hello")

	def test_node_childs(self):
		string = '''test_node {
	child1
	child2
	"string data"
	20000
	false
	3.149
}'''
		node = dfml.Node.create("test_node")
		node.add_child(dfml.Node.create("child1"))
		node.add_child(dfml.Node.create("child2"))
		node.add_child(dfml.Data.create_string("string data"))
		node.add_child(dfml.Data.create_integer(20000))
		node.add_child(dfml.Data.create_boolean(False))
		node.add_child(dfml.Data.create_double(3.149))

		builder = dfml.Builder.create()
		self.assertEqual(builder.build_node(node), string)

	def test_node_childs_of_childs(self):

		string = """test_node {
	child1
	child2 {
		child3
	}
}"""

		node = dfml.Node.create("test_node")
		child = dfml.Node.create("child1")
		node.add_child(child)
		child = dfml.Node.create("child2")
		node.add_child(child)
		child.add_child(dfml.Node.create("child3"))

		builder = dfml.Builder.create()
		self.assertEqual(builder.build_node(node), string)

	def test_data_elements(self):
		data = dfml.Data.create_string("hello")
		builder = dfml.Builder.create()
		self.assertEqual(builder.build_data(data), '"hello"')
		data = dfml.Data.create_integer(20)
		self.assertEqual(builder.build_data(data), '20')
		data = dfml.Data.create_double(3.14)
		self.assertEqual(builder.build_data(data), '3.14')
		data = dfml.Data.create_boolean(True)
		self.assertEqual(builder.build_data(data), 'true')

	def test_node_attributes(self):
		node = dfml.Node.create("person")
		node.set_attr_string("name", "John")
		node.set_attr_string("last", "Doe")
		node.set_attr_integer("ages", 40)
		node.set_attr_double("height", 1.65)
		node.set_attr_boolean("single", True)

		test = 'person(name: "John", last: "Doe", ages: 40, height: 1.65, single: true)'

		builder = dfml.Builder.create()
		self.assertEqual(builder.build_node(node), test)

	def test_comments(self):
		node = dfml.Node.create("test_comments")
		node.add_child(dfml.Comment.create("comment 1"))
		node.add_child(dfml.Comment.create("comment 2"))

		test = """test_comments {
	/*comment 1*/
	/*comment 2*/
}"""
		builder = dfml.Builder.create()
		self.assertEqual(builder.build_node(node), test)

	def test_combined(self):
		test = '''animals {
	bird {
		/*A comment*/
		duck(fly: true, say: "qack", name: "Donald") {
			20
			30
			40
		}
	}
	pet {
		dog(fly: false, say: "guau", name: "Bob") {
			0.4
			true
		}
	}
}'''

		animals = dfml.Node.create("animals")
		bird = dfml.Node.create("bird")
		animals.add_child(bird)
		bird.add_child(dfml.Comment.create("A comment"))
		duck = dfml.Node.create("duck")
		bird.add_child(duck)
		duck.set_attr_boolean("fly", True)
		duck.set_attr_string("say", "qack")
		duck.set_attr_string("name", "Donald")
		duck.add_child(dfml.Data.create_integer(20))
		duck.add_child(dfml.Data.create_integer(30))
		duck.add_child(dfml.Data.create_integer(40))
		pet = dfml.Node.create("pet")
		animals.add_child(pet)
		dog = dfml.Node.create("dog")
		pet.add_child(dog)
		dog.set_attr_boolean("fly", False)
		dog.set_attr_string("say", "guau")
		dog.set_attr_string("name", "Bob")
		dog.add_child(dfml.Data.create_double(0.4))
		dog.add_child(dfml.Data.create_boolean(True))

		builder = dfml.Builder.create()
		self.assertEqual(builder.build_node(animals), test)

	def test_no_format(self):

		test = "test_node { child1 child2 { child3 } }"

		node = dfml.Node.create("test_node")
		child = dfml.Node.create("child1")
		node.add_child(child)
		child = dfml.Node.create("child2")
		node.add_child(child)
		child.add_child(dfml.Node.create("child3"))

		builder = dfml.Builder.create()
		builder.set_format(False)

		self.assertEqual(builder.build_node(node), test)

	def test_use_spaces(self):
		test = '''animals {
   bird {
      /*A comment*/
      duck(fly: true, say: "qack", name: "Donald") {
         20
         30
         40
      }
   }
   pet {
      dog(fly: false, say: "guau", name: "Bob") {
         0.4
         true
      }
   }
}'''

		animals = dfml.Node.create("animals")
		bird = dfml.Node.create("bird")
		animals.add_child(bird)
		bird.add_child(dfml.Comment.create("A comment"))
		duck = dfml.Node.create("duck")
		bird.add_child(duck)
		duck.set_attr_boolean("fly", True)
		duck.set_attr_string("say", "qack")
		duck.set_attr_string("name", "Donald")
		duck.add_child(dfml.Data.create_integer(20))
		duck.add_child(dfml.Data.create_integer(30))
		duck.add_child(dfml.Data.create_integer(40))
		pet = dfml.Node.create("pet")
		animals.add_child(pet)
		dog = dfml.Node.create("dog")
		pet.add_child(dog)
		dog.set_attr_boolean("fly", False)
		dog.set_attr_string("say", "guau")
		dog.set_attr_string("name", "Bob")
		dog.add_child(dfml.Data.create_double(0.4))
		dog.add_child(dfml.Data.create_boolean(True))

		builder = dfml.Builder.create()
		builder.set_format(True)
		builder.use_spaces_for_indent(True)
		builder.set_space_count(3)
		self.assertEqual(builder.build_node(animals), test)
