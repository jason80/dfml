import dfml

class Builder:
	"""
	A class to build a string representation of DFML elements.

	"""
	def create() -> "Builder":
		"""
		Factory method to create a Builder instance.

		Returns:
			Builder: A new Builder instance.
		"""
		return Builder()

	def __init__(self) -> None:
		"""
		Constructor for Builder.
		Initializes formatting options and indentation parameters.
		"""
		self.__format = True
		self.__use_spaces = False
		self.__space_count = 4
		self.__level = 0

	def set_format(self, f: bool) -> None:
		"""
		Set the formatting option.

		Args:
			f (bool): True to enable formatting, False otherwise.
		"""
		self.__format = f

	def use_spaces_for_indent(self, us: bool) -> None:
		"""
		Set whether to use spaces for indentation.

		Args:
			us (bool): True to use spaces, False to use tabs.
		"""
		self.__use_spaces = us

	def set_space_count(self, sc: int) -> None:
		"""
		Set the number of spaces for each level of indentation.

		Args:
			sc (int): The number of spaces.
		"""
		self.__space_count = sc

	def build_node(self, node: dfml.Node) -> str:
		"""
		Build a string representation of a Node.

		Args:
			node (dfml.Node): The Node to be represented.

		Returns:
			str: The string representation of the Node.
		"""
		result = self.indent() + node.get_name()

		if node.get_attr_keys():
			result += self.build_attributes(node)

		# Children
		children = node.get_children()
		if children:
			result += " {\n" if self.__format else " { "
			self.__level += 1

			for e in children:
				result += self.build_element(e) + ("\n" if self.__format else " ")

			self.__level -= 1
			result += self.indent() + "}"

		return result

	def build_data(self, data: dfml.Data) -> str:
		"""
		Build a string representation of a Data element.

		Args:
			data (dfml.Data): The Data element to be represented.

		Returns:
			str: The string representation of the Data element.
		"""
		return self.indent() + self.build_value(data.get_value())

	def build_value(self, value: dfml.Value) -> str:
		"""
		Build a string representation of a Value.

		Args:
			value (dfml.Value): The Value to be represented.

		Returns:
			str: The string representation of the Value.
		"""
		return f'"{value.get_value()}"' if value.get_type() == dfml.Value.STRING else value.get_value()

	def build_element(self, e: "dfml.Element") -> str:
		"""
		Build a string representation of an Element.

		Args:
			e ("dfml.Element"): The Element to be represented.

		Returns:
			str: The string representation of the Element.
		"""
		if e.get_element_type() == dfml.Element.NODE:
			return self.build_node(e)
		if e.get_element_type() == dfml.Element.DATA:
			return self.build_data(e)
		return self.build_comment(e)

	def build_attributes(self, node: "dfml.Node") -> str:
		"""
		Build a string representation of attributes.

		Args:
			node ("dfml.Node"): The Node containing attributes.

		Returns:
			str: The string representation of attributes.
		"""
		return '(' + ", ".join([f"{k}: {self.build_value(node.get_attr(k))}" for k in node.get_attr_keys()]) + ')'

	def build_comment(self, comment: dfml.Comment) -> str:
		"""
		Build a string representation of a Comment.

		Args:
			comment (dfml.Comment): The Comment to be represented.

		Returns:
			str: The string representation of the Comment.
		"""
		return f'{self.indent()}/*{comment.get_string()}*/'

	def indent(self) -> str:
		"""
		Generate the indentation string.

		Returns:
			str: The indentation string.
		"""
		if not self.__format:
			return ""
		if self.__level == 0:
			return ""

		ind = ' ' * self.__space_count

		result = ""
		for i in range(self.__level):
			result += ind if self.__use_spaces else '\t'

		return result
	