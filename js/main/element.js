

/**
 * Base class representing an element in the Dragonfly Markup Language (DFML) structure.
 *
 * @export
 * @class DFMLElement
 */
export class DFMLElement {
  
	/**
	 * Gets the type of the element.
	 * - NODE: 0 - Represents a node.
	 * - DATA: 1 - Represents a data (value only).
	 * - COMMENT: 2 - Represents a comment.
	 * @returns {number} the type of the element.
	 * 
	 * @memberof DFMLElement
	 */
	getElementType() {
		throw new Error('getElementType() must be implemented by subclass');
	}

	/**
	 * Constant representing a DFMLNode element type.
	 *
	 * @readonly
	 * @static
	 * @memberof DFMLElement
	 */
	static get NODE() {
		return 0;
	}
  
	/**
	 * Constant representing a DFMLData.
	 *
	 * @readonly
	 * @static
	 * @memberof DFMLElement
	 */
	static get DATA() {
		return 1;
	}
  
	/**
	 * Constant representing a DFMLComment element type.
	 *
	 * @readonly
	 * @static
	 * @memberof DFMLElement
	 */
	static get COMMENT() {
		return 2;
	}
  }
