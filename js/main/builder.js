import { DFMLNode } from "./node.js";
import { DFMLValue } from "./value.js";
import { DFMLComment } from "./comment.js";
import { DFMLData } from "./data.js";
import { DFMLElement } from "./element.js";

/**
 * Class responsible for building DFML representations as strings.
 *
 * @export
 * @class DFMLBuilder
 */
export class DFMLBuilder {
	/**
	 * Creates an instance of DFMLBuilder.
	 * @memberof DFMLBuilder
	 */
	constructor() {
	  this.level = 0;
	  this.format = true;
	  this.useSpaces = false;
	  this.spaceCount = 4;
	}
  
	/**
	 * Creates and returns a DFMLBuilder instance.
	 *
	 * @static
	 * @return {DFMLBuilder} the new DFMLBuilder instance.
	 * @memberof DFMLBuilder
	 */
	static create() {
	  return new DFMLBuilder();
	}
  
	/**
	 * Format the code.
	 * Enable indent and eol.
	 * 
	 * @param {boolean} f true for format.
	 * @memberof DFMLBuilder
	 */
	setFormat(f) {
	  this.format = f;
	}
  
	/**
	 * Use spaces for indent.
	 * Set the number of spaces with setSpaceCount() method.
	 *
	 * @param {boolean} us true for spaces indent.
	 * @memberof DFMLBuilder
	 */
	useSpacesForIndent(us) {
	  this.useSpaces = us;
	}
  
	/**
	 * Set the space count for indent.
	 *
	 * @param {number} count count of spaces.
	 * @memberof DFMLBuilder
	 */
	setSpaceCount(count) {
	  this.spaceCount = count;
	}
  
	/**
	 * Builds and returns the DFML representation of a DFMLNode.
	 *
	 * @param {DFMLNode} node the node to build.
	 * @return {string} The DFML representation of the DFMLNode.
	 * @memberof DFMLBuilder
	 */
	buildNode(node) {
	  let result = this.indent() + node.getName();
  
	  if (node.getAttrKeys().length > 0) {
		result += this.buildAttributes(node);
	  }
  
	  const children = node.getChildren();
	  if (children.length > 0) {
		result += this.format ? " {\n" : " { ";
		this.level++;
		children.forEach(child => {
		  result += this.buildElement(child) + (this.format ? "\n" : " ");
		});
		this.level--;
		result += this.indent() + "}";
	  }
  
	  return result;
	}

	/**
	 * Builds and returns the DFML representation of an DFMLElement.
	 *
	 * @param {DFMLElement} element The DFMLElement to build.
	 * @return {string} The DFML representation of the DFMLElement.
	 * @memberof DFMLBuilder
	 */
	buildElement(element) {
		if (element instanceof DFMLNode) {
			return this.buildNode(element);
		} else if (element instanceof DFMLData) {
			return this.buildData(element);
		} else if (element instanceof DFMLComment) {
			return this.buildComment(element);
		} else {
			throw new Error("Unrecognized element type.");
		}
	}
  
	/**
	 * @brief Builds and returns the DFML representation of a DFMLData.
	 * 
	 * @param {DFMLData} data The DFMLData to build.
	 * @return {string} The DFML representation of the DFMLData.
	 */
	buildData(data) {
	  return this.indent() + this.buildValue(data.getValue());
	}
  
	/**
	 * Builds and returns the DFML representation of a DFMLComment.
	 *
	 * @param {DFMLComment} comment The DFMLComment to build.
	 * @return {string} The DFML representation of the DFMLComment.
	 * @memberof DFMLBuilder
	 */
	buildComment(comment) {
	  return this.indent() + `/*${comment.getString()}*/`;
	}
  
	/**
	 * Builds and returns the DFML representation of a DFMLValue.
	 *
	 * @param {DFMLValue} value The DFMLValue to build.
	 * @return {string} The DFML representation of the DFMLValue.
	 * @memberof DFMLBuilder
	 */
	buildValue(value) {
	  if (value.getType() === DFMLValue.STRING) {
		var dbl = value.getValue().includes('"');
		var sgl = value.getValue().includes("'");

		if (dbl && sgl) {
			// Remove all '"'
			val = value.getValue().replace(/"/g, '');
			return `"${val}"`;
		} 

		if (dbl) return `'${value.getValue()}'`;

		return `"${value.getValue()}"`;

	  } else {
		return value.getValue();
	  }
	}
  
	/**
	 * Builds and returns the DFML representation of attributes for a DFMLNode.
	 *
	 * @param {DFMLNode} node The DFMLNode for which to build attributes.
	 * @return {string} The DFML representation of attributes for the DFMLNode.
	 * @memberof DFMLBuilder
	 */
	buildAttributes(node) {
	  const attrs = node.getAttrKeys().map(key => {
		return `${key}: ${this.buildValue(node.getAttr(key))}`;
	  }).join(', ');
  
	  return `(${attrs})`;
	}
  
	
	/**
	 * Gets the current indentation based on the builder's level.
	 *
	 * @return {string} The current indentation.
	 * @memberof DFMLBuilder
	 */
	indent() {
	  if (!this.format || this.level === 0) return '';
  
	  const indentString = this.useSpaces ? ' '.repeat(this.spaceCount) : '\t';
	  return indentString.repeat(this.level);
	}
  }
  