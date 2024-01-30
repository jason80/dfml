import element
import value

class Data(element.Element):
	"""
	Represents a data element.

	"""
	def create() -> "Data":
		"""
		Factory method to create an empty Data instance.

		Returns:
			Data: An empty Data instance.
		"""
		return Data()

	def create(value: value.Value) -> "Data":
		"""
		Factory method to create a Data instance with a specific value.

		Args:
			value (value.Value): The value for the Data instance.

		Returns:
			Data: A Data instance with the specified value.
		"""
		return Data(value)

	def create_string(string: str) -> "Data":
		"""
		Factory method to create a Data instance with a string value.

		Args:
			string (str): The string value for the Data instance.

		Returns:
			Data: A Data instance with the specified string value.
		"""
		data = Data()
		data.get_value().set_string(string)
		return data

	def create_integer(number: int) -> "Data":
		"""
		Factory method to create a Data instance with an integer value.

		Args:
			number (int): The integer value for the Data instance.

		Returns:
			Data: A Data instance with the specified integer value.
		"""
		data = Data()
		data.get_value().set_integer(number)
		return data

	def create_double(number: float) -> "Data":
		"""
		Factory method to create a Data instance with a double value.

		Args:
			number (float): The double value for the Data instance.

		Returns:
			Data: A Data instance with the specified double value.
		"""
		data = Data()
		data.get_value().set_double(number)
		return data

	def create_boolean(bln: bool) -> "Data":
		"""
		Factory method to create a Data instance with a boolean value.

		Args:
			bln (bool): The boolean value for the Data instance.

		Returns:
			Data: A Data instance with the specified boolean value.
		"""
		data = Data()
		data.get_value().set_boolean(bln)
		return data

	def __init__(self, value: value.Value = None) -> None:
		"""
		Constructor for Data.

		Args:
			value (value.Value): The value for the Data instance.
		"""
		self.__value = value
		if value is None:
			self.__value = value.Value()

	def get_value(self) -> value.Value:
		"""
		Get the value of the data.

		Returns:
			value.Value: The value of the data.
		"""
		return self.__value

	def get_element_type(self) -> int:
		"""
		Get the element type (DATA).

		Returns:
			int: The element type.
		"""
		return element.Element.DATA
