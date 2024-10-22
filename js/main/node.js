import { DFMLElement } from "./element.js"
import { DFMLValue } from "./value.js"

/**
 * Class representing a node in the Dragonfly Markup Language (DFML).
 * This class inherits from the base class Element and provides functionalities for the manipulation
 * and management of nodes in the DFML data structure.
 *
 * @export
 * @class DFMLNode
 * @extends {DFMLElement}
 */
export class DFMLNode extends DFMLElement {
	/**
	 * Creates an instance of DFMLNode.
	 * @memberof DFMLNode
	 */
	constructor() {
		super();
		this.name = '';
		this.attrs = new Map();
		this.keys = [];
		this.children = [];
	}

	/**
	 * Creates and returns a an instance of Node with the specified name.
	 *
	 * @static
	 * @param {string} name The name of the node.
	 * @return {DFMLNode} the new instance of Node.
	 * @memberof DFMLNode
	 */
	static create(name) {
		const node = new DFMLNode();
		node.setName(name);
		return node;
	}

	/**
	 * Sets the name of the node.
	 *
	 * @param {string} name The name to set for the node.
	 * @memberof DFMLNode
	 */
	setName(name) {
		this.name = name;
	}

	/**
	 * Gets the name of the node.
	 *
	 * @return {string} The name of the node.
	 * @memberof DFMLNode
	 */
	getName() {
		return this.name;
	}

	/**
	 * Returns the element type as an integer, identifying it as a node.
	 *
	 * @return {number} The element type (NODE).
	 * @memberof DFMLNode
	 */
	getElementType() {
		return DFMLElement.NODE;
	}

	/**
	 * Adds a child element to the node.
	 *
	 * @param {DFMLElement} element The child element to add.
	 * @memberof DFMLNode
	 */
	addChild(element) {
		this.children.push(element);
	}

	/**
	 * Sets an attribute for the node with the given value.
	 *
	 * @param {string} name The name of the attribute.
	 * @param {DFMLValue} value The value of the attribute.
	 * @memberof DFMLNode
	 */
	setAttribute(name, value) {
		if (!this.hasAttr(name)) {
			this.keys.push(name);
		}
		this.attrs.set(name, value);
	}

	/**
	 * Sets a string attribute for the node.
	 *
	 * @param {string} name The name of the attribute.
	 * @param {string} value The value of the attribute as a string.
	 * @memberof DFMLNode
	 */
	setAttrString(name, value) {
		const val = new DFMLValue();
		val.setString(value);
		this.setAttribute(name, val);
	}

	/**
	 * Sets an integer attribute for the node.
	 *
	 * @param {string} name The name of the attribute.
	 * @param {number} value The value of the attribute as an integer.
	 * @memberof DFMLNode
	 */
	setAttrInteger(name, value) {
		const val = new DFMLValue();
		val.setInteger(value);
		this.setAttribute(name, val);
	}

	/**
	 * Sets a double attribute for the node.
	 *
	 * @param {string} name The name of the attribute.
	 * @param {number} value The value of the attribute as a double.
	 * @memberof DFMLNode
	 */
	setAttrDouble(name, value) {
		const val = new DFMLValue();
		val.setDouble(value);
		this.setAttribute(name, val);
	}

	/**
	 * Sets a boolean attribute for the node.
	 *
	 * @param {string} name The name of the attribute.
	 * @param {boolean} value The value of the attribute as a boolean.
	 * @memberof DFMLNode
	 */
	setAttrBoolean(name, value) {
		const val = new DFMLValue();
		val.setBoolean(value);
		this.setAttribute(name, val);
	}

	/**
	 * Gets the value of an attribute given its name.
	 *
	 * @param {string} name The name of the attribute.
	 * @return {DFMLValue} The value object of the attribute.
	 * @memberof DFMLNode
	 */
	getAttr(name) {
		return this.attrs.get(name);
	}

	/**
	 * Checks if the node has an attribute given its name.
	 *
	 * @param {string} name The name of the attribute.
	 * @return {boolean} true if the node has the attribute.
	 * @memberof DFMLNode
	 */
	hasAttr(name) {
		return this.attrs.has(name);
	}

	/**
	 * Gets the attribute keys in added order.
	 *
	 * @return {Array.<string>} attribute key list.
	 * @memberof DFMLNode
	 */
	getAttrKeys() {
		return this.keys;
	}

	/**
	 * Gets the list of child elements of the node.
	 *
	 * @return {Array.<DFMLElement>} List of child elements.
	 * @memberof DFMLNode
	 */
	getChildren() {
		return this.children;
	}
}
