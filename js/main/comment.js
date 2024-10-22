import { DFMLElement } from "./element.js"

/**
 * Class representing a comment element in the Dragonfly Markup Language (DFML).
 *
 * @export
 * @class DFMLComment
 * @extends {DFMLElement}
 */
export class DFMLComment extends DFMLElement {
	/**
	 * Creates an instance of DFMLComment.
	 * @param {string} [content=""] content text of the comment.
	 * @memberof DFMLComment
	 */
	constructor(content = "") {
		super();
		this.content = content;
	}
  
	/**
	 * Creates and returns a shared pointer to an empty DFMLComment instance.
	 *
	 * @static
	 * @return {DFMLComment} the new DFMLComment instance.
	 * @memberof DFMLComment
	 */
	static create() {
		return new DFMLComment();
	}

	/**
	 * Creates and returns a DFMLComment instance with the specified string content.
	 *
	 * @static
	 * @param {string} content the content of the comment.
	 * @return {*} the new DFMLComment instance.
	 * @memberof DFMLComment
	 */
	static createWithContent(content) {
		const comment = this.create(); 
		comment.setString(content); 
		return comment; 
	}
  
	/**
	 * Sets the string content of the comment.
	 *
	 * @param {string} content The content to set for the comment.
	 * @memberof DFMLComment
	 */
	setString(content) {
		this.content = content;
	}
  
	/**
	 * Gets the string content of the comment.
	 *
	 * @return {string} The content of the comment.
	 * @memberof DFMLComment
	 */
	getString() {
		return this.content;
	}
  
	/**
	 * Gets the element type as an integer, identifying it as a comment.
	 *
	 * @return {number} 
	 * @override
	 * @memberof DFMLComment The element type (COMMENT).
	 */
	getElementType() {
		return DFMLElement.COMMENT;
	}
  }
