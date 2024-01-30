from abc import ABC, abstractmethod

class Element(ABC):
	"""
	Abstract base class representing an element in a hierarchical structure.
	
	Attributes:
		NODE (int): Constant representing a node element.
		DATA (int): Constant representing a data element.
		COMMENT (int): Constant representing a comment element.
	"""
	NODE = 0
	DATA = 1
	COMMENT = 2

	@abstractmethod
	def get_element_type(self) -> int:
		"""
		Abstract method to get the type of the element.

		Returns:
			int: An integer representing the type of the element.
		"""
		pass
