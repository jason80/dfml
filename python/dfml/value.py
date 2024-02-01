class Value:
	"""
	Represents a value with a specific type.

	Attributes:
		STRING (int): Constant representing a string value.
		INTEGER (int): Constant representing an integer value.
		DOUBLE (int): Constant representing a double value.
		BOOLEAN (int): Constant representing a boolean value.

	"""
	STRING = 0
	INTEGER = 1
	DOUBLE = 2
	BOOLEAN = 3

	def __init__(self) -> None:
		"""
		Constructor for Value.
		"""
		self.__type = Value.STRING
		self.__value = ""

	def get_type(self) -> int:
		"""
		Get the type of the value.

		Returns:
			int: The type of the value.
		"""
		return self.__type

	def set_string(self, string: str) -> None:
		"""
		Set the value as a string.

		Args:
			string (str): The string value.
		"""
		self.__value = string
		self.__type = Value.STRING

	def set_integer(self, number: int) -> None:
		"""
		Set the value as an integer.

		Args:
			number (int): The integer value.
		"""
		self.__value = str(number)
		self.__type = Value.INTEGER

	def set_double(self, number: float) -> None:
		"""
		Set the value as a double.

		Args:
			number (float): The double value.
		"""
		self.__value = str(number)
		self.__type = Value.DOUBLE

	def set_boolean(self, bln: bool) -> None:
		"""
		Set the value as a boolean.

		Args:
			bln (bool): The boolean value.
		"""
		self.__value = "true" if bln else "false"
		self.__type = Value.BOOLEAN

	def get_value(self) -> str:
		"""
		Get the value.

		Returns:
			str: The string value
		"""
		return self.__value
