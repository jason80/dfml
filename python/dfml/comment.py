import element

class Comment(element.Element):
	"""
	Represents a comment element.

	"""
	def create(string: str = "") -> "Comment":
		"""
		Factory method to create a Comment instance.

		Args:
			string (str): The comment string.

		Returns:
			Comment: A Comment instance.
		"""
		return Comment(string)

	def __init__(self, string: str) -> None:
		"""
		Constructor for Comment.

		Args:
			string (str): The comment string.
		"""
		self.__string = string

	def get_element_type(self) -> int:
		"""
		Get the element type (COMMENT).

		Returns:
			int: The element type.
		"""
		return element.Element.COMMENT

	def get_string(self) -> str:
		"""
		Get the comment string.

		Returns:
			str: The comment string.
		"""
		return self.__string

	def set_string(self, string: str) -> None:
		"""
		Set the comment string.

		Args:
			string (str): The new comment string.
		"""
		self.__string = string
