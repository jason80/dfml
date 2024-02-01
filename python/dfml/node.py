import dfml
import typing

class Node(dfml.Element):
	"""
	Represents a node in a hierarchical structure.
	"""

	@staticmethod
	def create(name: str) -> "Node":
		"""
		Factory method to create a new Node instance.

		Args:
			name (str): The name of the node.

		Returns:
			Node: A new Node instance.
		"""
		return Node(name)

	def __init__(self, name: str = "") -> None:
		"""
		Constructor for Node.

		Args:
			name (str): The name of the node.
		"""
		super().__init__()
		self.__name = name
		self.__attributes = {}
		self.__children = []

	def get_element_type(self) -> int:
		"""
		Get the type of the element.

		Returns:
			int: The element type (Node).
		"""
		return dfml.Element.NODE
	
	def get_name(self) -> str:
		"""
		Get the name of the node.

		Returns:
			str: The name of the node.
		"""
		return self.__name
	
	def set_name(self, name: str) -> None:
		"""
		Set the name of the node.

		Args:
			name (str): The new name for the node.
		"""
		self.__name = name

	def add_child(self, element: dfml.Element) -> None:
		"""
		Add a child element to the node.

		Args:
			element (element.Element): The child element to add.
		"""
		self.__children.append(element)

	def get_children(self) -> typing.List[dfml.Element]:
		"""
		Get the list of child elements.

		Returns:
			typing.List[element.Element]: The list of child elements.
		"""
		return self.__children

	def set_attribute(self, name: str, value: "dfml.Value") -> None:
		"""
		Set an attribute for the node.

		Args:
			name (str): The name of the attribute.
			value (value.Value): The value of the attribute.
		"""
		self.__attributes[str] = value

	def set_attr_string(self, name: str, string: str) -> None:
		"""
		Set a string attribute for the node.

		Args:
			name (str): The name of the attribute.
			string (str): The string value of the attribute.
		"""
		v = dfml.Value()
		v.set_string(string)
		self.__attributes[name] = v

	def set_attr_integer(self, name: str, number: int) -> None:
		"""
		Set an integer attribute for the node.

		Args:
			name (str): The name of the attribute.
			number (int): The integer value of the attribute.
		"""
		v = dfml.Value()
		v.set_integer(number)
		self.__attributes[name] = v

	def set_attr_double(self, name: str, number: float) -> None:
		"""
		Set a double attribute for the node.

		Args:
			name (str): The name of the attribute.
			number (float): The double value of the attribute.
		"""
		v = dfml.Value()
		v.set_double(number)
		self.__attributes[name] = v

	def set_attr_boolean(self, name: str, boolean: int) -> None:
		"""
		Set a boolean attribute for the node.

		Args:
			name (str): The name of the attribute.
			boolean (int): The boolean value of the attribute.
		"""
		v = dfml.Value()
		v.set_boolean(boolean)
		self.__attributes[name] = v

	def get_attr(self, name: str) -> "dfml.Value":
		"""
		Get the value of a specific attribute.

		Args:
			name (str): The name of the attribute.

		Returns:
			value.Value: The value of the attribute.
		"""
		return self.__attributes[name]
	
	def has_attr(self, name: str) -> bool:
		"""
		Check if the node has a specific attribute.

		Args:
			name (str): The name of the attribute.

		Returns:
			bool: True if the node has the attribute, False otherwise.
		"""
		return name in self.__attributes

	def get_attr_keys(self) -> typing.List[str]:
		"""
		Get the list of attribute keys.

		Returns:
			typing.List[str]: The list of attribute keys.
		"""
		return list(self.__attributes)
