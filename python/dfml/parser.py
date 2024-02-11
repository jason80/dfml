import typing
import dfml

class ParserException(Exception):
	"""
	Exception class for parser-related errors.

	Attributes:
		message (str): The error message associated with the exception.

	Example:
		>>> raise ParserException("Error in parsing data.")
		ParserException: Error in parsing data.
	"""

	def __init__(self, message: str) -> None:
		"""
		Constructor for the ParserException class.

		Args:
			message (str): The error message associated with the exception.
		"""
		super().__init__(message)
		self.message = message

	def __str__(self) -> str:
		"""
		Returns the error message associated with the exception.

		Returns:
			str: The error message as a string.
		"""
		return self.message

class CharIterator:
	"""
	Iterator class for characters in a string.

	"""
	def __init__(self) -> None:
		"""Constructor for CharIterator."""
		self.set_data("")

	def set_data(self, data: str) -> None:
		"""
		Set the data for iteration.

		Args:
			data (str): The string data to iterate over.
		"""
		self.__data = data
		self.__i = 0
		self.__line = 1

	def next(self) -> str:
		"""
		Get the next character in the iteration.

		Returns:
			str: The next character.
		"""
		if self.__i >= len(self.__data):
			return ""

		ch = self.__data[self.__i]
		self.__i += 1
		if ch == '\n':
			self.__line += 1
		return ch

	def back(self) -> None:
		"""Move the iterator back by one character."""
		self.__i -= 1

	def current(self) -> str:
		"""
		Get the current character.

		Returns:
			str: The current character.
		"""
		return self.__data[self.__i - 1]

	def end(self) -> bool:
		"""
		Check if the end of the data is reached.

		Returns:
			bool: True if the end is reached, False otherwise.
		"""
		return self.__i >= len(self.__data)

	def get_line(self) -> str:
		return str(self.__line)

class Parser:
	"""
	Parser class for parsing DFML strings into elements.

	"""
	def create(string: str) -> "Parser":
		"""
		Factory method to create a Parser instance.

		Args:
			string (str): The DFML string to parse.

		Returns:
			Parser: A new Parser instance.
		"""
		return Parser(string)

	def __init__(self, string: str) -> None:
		"""
		Constructor for Parser.

		Args:
			string (str): The DFML string to parse.
		"""
		self.__i = CharIterator()
		self.__i.set_data(string)

	def parse(self) -> typing.List[dfml.Element]:
		"""
		Parse the DFML string.

		Returns:
			typing.List[dfml.Element]: A list of parsed DFML elements.
		"""
		return self.parse_children()

	def parse_children(self) -> typing.List[dfml.Element]:
		"""
		Parse the children of a node.

		Returns:
			typing.List[dfml.Element]: A list of parsed DFML elements.
		"""
		ch = ""
		childs = []
		while True:
			ch = self.__i.next()
			if ch == "":
				break

			if ch == ' ' or ch == '\t' or ch == '\n' or ch == '\r':
				continue

			if ch == '/' or ch == '#':
				self.__i.back()
				childs.append(self.parse_comment())
				continue

			if ch == '"' or ch == "'":
				value = self.parse_string()
				childs.append(dfml.Data.create(value))
				continue

			if ch == '}':
				return childs

			if self.is_alpha(ch):
				self.__i.back()
				childs.append(self.parse_node())
			elif self.is_number(ch):
				self.__i.back()
				value = self.parse_number()
				childs.append(dfml.Data.create(value))
			else:
				breakpoint()
				raise ParserException("Invalid character for node child on line: " +
						self.__i.get_line())

		return childs

	def parse_node(self) -> dfml.Element:
		"""
		Parse a DFML node.

		Returns:
			dfml.Element: The parsed DFML node.
		"""
		ch = ""
		name = self.parse_node_name()

		# If keywords "true" or "false" isn't a node: it is boolean data.
		if name == "true":
			return dfml.Data.create_boolean(True)
		elif name == "false":
			return dfml.Data.create_boolean(False)

		node = dfml.Node.create(name)

		if self.__i.end():
			return node

		self.__i.back()

		if not node.get_name():
			raise ParserException("Empty node name encountered on line: " + self.__i.get_line())

		attr_parsed = False
		children = []

		while True:
			ch = self.__i.next()
			if ch == "":
				break

			if ch == ' ' or ch == '\t' or ch == '\n' or ch == '\r':
				continue

			if ch == '(':
				if attr_parsed:
					raise ParserException("Double attribute list found in the node on line: " +
						self.__i.get_line())
				
				self.parse_node_attributes(node)
				attr_parsed = True
				break

			if ch == '{':
				children = self.parse_children()
				break

			if ch == '}':
				break

			self.__i.back()
			break

		# Set childs
		for e in children:
			node.add_child(e)

		return node

	def parse_node_name(self) -> str:
		"""
		Parse the name of a node.

		Returns:
			str: The name of the node.
		"""
		ch = ""
		name = ""
		while True:
			ch = self.__i.next()
			if ch == "":
				break

			if self.is_alphanum(ch):
				name += ch
			else:
				break

		return name

	def parse_node_attributes(self, node: dfml.Node) -> None:
		"""
		Parse the attributes of a node.

		Args:
			node (dfml.Node): The node to which the attributes belong.
		"""
		ch = ""
		while True:
			ch = self.__i.next()
			if ch == "":
				break

			if ch == ' ' or ch == '\n' or ch == '\t' or ch == '\r':
				continue

			if ch == ',':
				raise ParserException("Unexpected attribute pair separator ',': " + self.__i.get_line())

			if ch == ')':
				break

			if self.is_alpha(ch):
				self.__i.back()
				self.parse_node_attribute(node)

	def parse_node_attribute(self, node: dfml.Node) -> None:
		"""
		Parse a single attribute of a node.

		Args:
			node (dfml.Node): The node to which the attribute belongs.
		"""
		PARSING_NAME = 0
		FIND_SEP = 1
		FIND_VALUE = 2

		status = PARSING_NAME
		key = ""

		while True:
			ch = self.__i.next()
			if ch == "":
				break

			if status == FIND_VALUE:
				if ch == ' ' or ch == '\n' or ch == '\t' or ch == '\r':
					continue

				if ch == '"' or ch == "'":
					value = self.parse_string()
					node.set_attribute(key, value)

				if ch == ',':
					# End of pair
					return None
				
				if ch == ')':
					self.__i.back()
					return None

				if self.is_number(ch):
					self.__i.back()
					value = self.parse_number()
					node.set_attribute(key, value)
					self.__i.back()

				if self.is_alpha(ch):
					self.__i.back()
					value = self.parse_boolean()
					node.set_attribute(key, value)
					self.__i.back()

			elif status == FIND_SEP:
				if ch == ' ' or ch == '\n' or ch == '\t' or ch == '\r':
					continue

				if ch == ':':
					status = FIND_VALUE

				if ch == ',' or ch == ')':
					node.set_attr_string(key, "")
					return None
			elif status == PARSING_NAME:
				if ch == ' ' or ch == '\n' or ch == '\t' or ch == '\r' or ch == ':':
					status = FIND_SEP
					self.__i.back()
				elif ch == ',' or ch == ')':
					node.set_attr_string(key, "")
					return None
				elif self.is_alphanum(ch):
					key += ch

	def parse_string(self) -> dfml.Value:
		"""
		Parse a string value.

		Returns:
			dfml.Value: The parsed string value.
		"""
		result = ""
		ch = ""
		end = self.__i.current()

		while True:
			ch = self.__i.next()
			if ch == "" or ch == end:
				break
			result += ch

		value = dfml.Value()
		value.set_string(result)
		return value

	def parse_number(self) -> dfml.Value:
		"""
		Parse a numeric value.

		Returns:
			dfml.Value: The parsed numeric value.
		"""
		ch = ""
		result = ""
		dbl = False
		while True:
			ch = self.__i.next()
			if ch == "":
				break
			if not self.is_number(ch):
				break
			if ch == '.':
				dbl = True

			result += ch

		value = dfml.Value()

		if dbl:
			try:
				value.set_double(float(result))
			except:
				raise ParserException("Double conversion error on line: " + self.__i.get_line())
		else:
			try:
				value.set_integer(int(result))
			except:
				raise ParserException("Integer conversion error on line: " + self.__i.get_line())

		return value

	def parse_boolean(self) -> dfml.Value:
		"""
		Parse a boolean value.

		Returns:
			dfml.Value: The parsed boolean value.
		"""
		ch = ""
		result = ""
		value = dfml.Value()

		while True:
			ch = self.__i.next()
			if ch == "":
				break
			if not self.is_alpha(ch):
				break

			result += ch

		if result == "true" or result == "false":
			value.set_boolean(result == "true")
		else:
			raise ParserException("Boolean conversion error on line: " + self.__i.get_line())

		return value

	def parse_comment(self) -> dfml.Element:
		"""
		Parse a comment.

		Returns:
			dfml.Element: The parsed comment.
		"""
		ch = self.__i.next()
		single_line = False
		string = ""

		if ch == '#':
			single_line = True
		elif ch == '/':
			ch = self.__i.next()
			if ch == "":
				raise ParserException("Unexpected comment termination on line: " + self.__i.get_line())
			elif ch == '/':
				single_line = True
			elif ch == '*':
				single_line = False
			else:
				raise ParserException("Unexpected comment termination on line: " + self.__i.get_line())

		while True:
			ch = self.__i.next()
			if ch == "":
				break

			elif ch == '\r':
				if not single_line:
					string += ch

			elif ch == '\n':
				if single_line:
					self.__i.back()
					break
				else:
					string += ch

			elif ch == '*':
				if not single_line:
					ch = self.__i.next()
					if ch == '/' or ch == '':
						break
					else:
						string += ch

			else:
				string += ch

		return dfml.Comment.create(string)

	def is_alpha(self, ch: str) -> bool:
		"""
		Check if a character is an alphabetic character.

		Args:
			ch (str): The character to check.

		Returns:
			bool: True if the character is alphabetic, False otherwise.
		"""
		if ch.isalpha():
			return True
		elif ch == '_':
			return True
		return False

	def is_alphanum(self, ch: str) -> bool:
		"""
		Check if a character is an alphanumeric character.

		Args:
			ch (str): The character to check.

		Returns:
			bool: True if the character is alphanumeric, False otherwise.
		"""
		if self.is_alpha(ch):
			return True
		elif ch.isdigit():
			return True
		return False

	def is_number(self, ch: str) -> bool:
		"""
		Check if a character is part of a numeric value.

		Args:
			ch (str): The character to check.

		Returns:
			bool: True if the character is part of a numeric value, False otherwise.
		"""
		if (ch.isdigit()):
			return True
		elif ch == '.' or ch == '-':
			return True
		return False
