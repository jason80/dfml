import { DFMLNode } from "./node.js"
import { DFMLData } from "./data.js"
import { DFMLValue } from "./value.js";
import { DFMLComment } from "./comment.js"
import { DFMLElement } from "./element.js";

/**
 * Exception class for parser-related errors.
 *
 * @class DFMLParserException
 * @extends {Error}
 */
class DFMLParserException extends Error {
	/**
	 * Creates an instance of DFMLParserException.
	 * @param {string} message message of the exception.
	 * @memberof DFMLParserException
	 */
	constructor(message) {
		super(message);
		this.name = "DFMLParserException";
	}
}

/**
 * Iterator for characters used by the Parser to iterate over a string.
 *
 * @class CharIterator
 */
class CharIterator {
	/**
	 * Creates an instance of CharIterator.
	 * @param {string} [data=''] string data.
	 * @memberof CharIterator
	 */
	constructor(data = '') {
		this.data = data;
		this.i = 0;
		this.line = 1;
	}

	/**
	 * Sets the data for iteration.
	 *
	 * @param {string} data The string data to iterate over.
	 * @memberof CharIterator
	 */
	setData(data) {
		this.data = data;
		this.i = 0;
		this.line = 1;
	}

	/**
	 * Retrieves the next character in the iteration.
	 *
	 * @return {number} The ASCII value of the next character.
	 * @memberof CharIterator
	 */
	next() {
		if (this.i >= this.data.length) return -1;
		const ch = this.data[this.i++];
		if (ch === '\n') this.line++;
		return ch.charCodeAt(0);
	}

	/**
	 * Retrieves the current character in the iteration.
	 *
	 * @return {number} The ASCII value of the current character.
	 * @memberof CharIterator
	 */
	current() {
		return this.data[this.i - 1];
	}

	/**
	 * Moves the iterator back to the previous character.
	 *
	 * @memberof CharIterator
	 */
	back() {
		this.i--;
	}

	/**
	 * Checks if the end of the iteration is reached.
	 *
	 * @return {boolean} True if the end is reached, false otherwise.
	 * @memberof CharIterator
	 */
	end() {
		return this.i >= this.data.length;
	}

	/**
	 * Returns current data line.
	 *
	 * @return {string} the current data line.
	 * @memberof CharIterator
	 */
	getLine() {
		return this.line.toString();
	}
}

/**
 * Class responsible for parsing DFML data and creating DFML objects.
 *
 * @export
 * @class DFMLParser
 */
export class DFMLParser {
	/**
	 * Creates an instance of DFMLParser.
	 * @param {string} data The DFML data to parse.
	 * @memberof DFMLParser
	 */
	constructor(data) {
		this.i = new CharIterator(data);
	}

	/**
	 * Creates and returns a DFMLParser instance.
	 *
	 * @static
	 * @param {string} data The DFML data to parse.
	 * @return {DFMLParser} the new DFMLParser instance.
	 * @memberof DFMLParser
	 */
	static create(data) {
		return new DFMLParser(data);
	}

	/**
	 * Parses the DFML data and returns a list of parsed DFMLElement objects.
	 *
	 * @return {Array.<DFMLElement>} The list of parsed DFMLElement objects.
	 * @memberof DFMLParser
	 */
	parse() {
		const list = [];
		this.parseChildren(list);
		return list;
	}

	/**
	 *  Parses the children of a DFMLNode.
	 *
	 * @param {Array.<DFMLElement>} childs The list to store the parsed child elements.
	 * @memberof DFMLParser
	 */
	parseChildren(childs) {
		let ch;
		let value = new DFMLValue();
		while ((ch = this.i.next()) !== -1) {
			switch (ch) {
				case 32: // space
				case 9:  // tab
				case 10: // newline
				case 13: // carriage return 
					break;

				case 47: // '/'
				case 35: // '#'
					this.i.back();
					childs.push(this.parseComment());
					break;

				case 34: // '"'
				case 39: // "'"
					value = new DFMLValue();
					this.parseString(value);
					childs.push(DFMLData.createWithValue(value));
					break;

				case 125: // '}'
					return;

				default:
					//if (/[a-zA-Z]/.test(String.fromCharCode(ch))) {
					if (this.isAlpha(ch)) {
						this.i.back();
						childs.push(this.parseNode());
					} else if (/[0-9]/.test(String.fromCharCode(ch))) {
						this.i.back();
						value = new DFMLValue();
						this.parseNumber(value);
						childs.push(DFMLData.createWithValue(value));
					} else {
						throw new DFMLParserException("Invalid character for node child on line: " + this.i.getLine());
					}
			}
		}
	}

	/**
	 * Parses a DFMLNode element.
	 *
	 * @return {DFMLNode} The parsed DFMLNode element.
	 * @memberof DFMLParser
	 */
	parseNode() {
		let ch;
		const name = this.parseNodeName();

		if (name === "true") return DFMLData.createBoolean(true);
		if (name === "false") return DFMLData.createBoolean(false);

		const node = DFMLNode.create(name);
		let children = [];

		if (this.i.end()) return node;

		this.i.back();

		if (!node.name) {
			throw new DFMLParserException("Empty node name encountered on line: " + this.i.getLine());
		}

		let stop = false;
		let attrParsed = false;

		while ((ch = this.i.next()) !== -1) {
			switch (ch) {
				case 32:
				case 9:
				case 10:
				case 13:
					break; // space (continue)

				case 40: // '('
					if (attrParsed) {
						throw new DFMLParserException("Double attribute list found in the node on line: " + this.i.getLine());
					}
					this.parseNodeAttributes(node);
					attrParsed = true;
					break;

				case 123: // '{'
					this.parseChildren(children);
					stop = true;
					break;

				case 125: // '}'
					stop = true;
					this.i.back();
					break;

				default:
					stop = true;
					this.i.back();
					break;
			}

			if (stop) break;
		}

		children.forEach((c) => {
			node.addChild(c);
		});

		return node;
	}

	/**
	 * Parses the name of a DFMLNode element.
	 *
	 * @return {string} The parsed name of the DFMLNode element.
	 * @memberof DFMLParser
	 */
	parseNodeName() {
		let name = '';
		let ch;
		while ((ch = this.i.next()) !== -1) {
			//if (/[a-zA-Z0-9]/.test(String.fromCharCode(ch))) {
			if (this.isAlphaNum(ch)) {
				name += String.fromCharCode(ch);
			} else break;
		}
		return name;
	}

	/**
	 * Parse attibutes for the given node.
	 *
	 * @param {DFMLNode} node The node reference.
	 * @memberof DFMLParser
	 */
	parseNodeAttributes(node) {
		let ch;
		let stop = false;

		while ((ch = this.i.next()) !== -1 && !stop) {
			switch (ch) {
				case 32:
				case 9:
				case 10:
				case 13:
					break;

				case 41: // ')'
					stop = true;
					break;
			}

			//if (/[a-zA-Z]/.test(String.fromCharCode(ch))) {
			if (this.isAlpha(ch)) {
				this.i.back();
				this.parseNodeAttribute(node);
			}

			if (stop) break;
		}
	}

	/**
	 * Parse a attribute pair (Key/Value) for the given node.
	 *
	 * @param {DFMLNode} node The node reference.
	 * @memberof DFMLParser
	 */
	parseNodeAttribute(node) {
		let key = '';
		let value = new DFMLValue();
		let status = 'PARSING_NAME';
		let ch;

		while ((ch = this.i.next()) !== -1) {
			switch (status) {
				case 'FIND_VALUE':
					if (ch === 34 || ch === 39) { // '  "
						this.parseString(value);
						//node[key] = value;
						node.setAttribute(key, value);
					//} else if (/[0-9]/.test(String.fromCharCode(ch))) {
					} else if (this.isNumber(ch)) {
						this.i.back();
						this.parseNumber(value);
						node.setAttribute(key, value);
						this.i.back();
					//} else if (/[a-zA-Z]/.test(String.fromCharCode(ch))) {
					} else if (this.isAlpha(ch)) {
						this.i.back();
						this.parseBoolean(value);
						node.setAttribute(key, value);
						this.i.back();
					} else if (ch === 32 || ch === 10 || ch === 9 || ch === 8 || ch === 13) {

					} else if (ch === 44) { // ,
						return ;
					} else if (ch === 41) { // )
						this.i.back();
						return ;
					}

				case 'FIND_SEP':
					if (ch === 58) status = 'FIND_VALUE'; // ':'
					break;

				case 'PARSING_NAME':
					if (ch === 32 || ch === 10 || ch === 9 || ch === 8 || ch === 13
							|| ch === 58) { // :
						status = 'FIND_SEP';
						this.i.back();
					} else if (ch === 44 || ch === 41) { // ,  (
						// Empty attribute
						node.setAttrString(key, "");
						this.i.back();
						return ;
					//} else if (/[a-zA-Z0-9_]/.test(String.fromCharCode(ch))) {
					} else if (this.isAlphaNum(ch)) {
						key += String.fromCharCode(ch);
					}
					break;
			}
		}
	}

	/**
	 * Parses a string DFMLData element.
	 *
	 * @param {DFMLValue} value value to set string data.
	 * @memberof DFMLParser
	 */
	parseString(value) {
		let result = '';
		const end = this.i.current();
		let ch;
		while ((ch = this.i.next()) !== -1) {
			if (ch === end.charCodeAt(0)) break;
			result += String.fromCharCode(ch);
		}
		value.setString(result)
	}

	/**
	 * Parses a number DFMLData element.
	 * Autodetect float point to se double data or se fixed to integer.
	 * 
	 * @param {DFMLValue} value value to set number data.
	 * @memberof DFMLParser
	 */
	parseNumber(value) {
		let result = '';
		let ch;
		let dbl = false;

		while ((ch = this.i.next()) !== -1) {
			//if (!/[0-9.]/.test(String.fromCharCode(ch))) break;
			if (!this.isNumber(ch)) break;
			if (ch === 46) dbl = true;
			result += String.fromCharCode(ch);
		}

		if (dbl) {
			value.setDouble(parseFloat(result))
		} else {
			value.setInteger(parseInt(result, 10))
		}
	}

	/**
	 * Parses a boolean DFMLData element.
	 *
	 * @param {DFMLValue} value value to set boolean data.
	 * @memberof DFMLParser
	 */
	parseBoolean(value) {
		let result = '';
		let ch;
		while ((ch = this.i.next()) !== -1) {
			//if (!/[a-zA-Z]/.test(String.fromCharCode(ch))) break;
			if (!this.isAlpha(ch)) break;
			result += String.fromCharCode(ch);
		}
		if (result === "true" || result === "false") {
			value.setBoolean(result === "true");
		} else {
			throw new DFMLParserException("Boolean conversion error on line: " + this.i.getLine());
		}
	}

	/**
	 * Parses a DFMLComment element.
	 * Parses '//', '/*' and '#' comment type.
	 *
	 * @return {DFMLComment} The parsed DFMLComment element.
	 * @memberof DFMLParser
	 */
	parseComment() {
		let ch = this.i.next();
		let singleLine = false;
		let string = '';

		if (ch === 35) // #
			singleLine = true;
		else if (ch === 47) { // /
			ch = this.i.next();
			if (ch === -1)
				throw new DFMLParserException("Unexpected comment termination on line: " + this.i.getLine());
			else if (ch === 47) // /
				singleLine = true;
			else if (ch === 42) // *
				singleLine = false;
			else {
				throw new DFMLParserException("Unexpected comment termination on line: " + this.i.getLine());
			}
		}

		let stop = false;
		while ((ch = this.i.next()) !== -1 && !stop) {
			switch(ch) {
			case 13: // \r
				if (!singleLine) string += String.fromCharCode(ch);
				break;
			case 10: // \n
				if (singleLine) {
					this.i.back();
					stop = true;
				} else string += String.fromCharCode(ch);
				break;

			case 42: // *
				if (!singleLine) {
					ch = this.i.next();
					if (ch === 47 || ch === -1) // /
						stop = true;
					else
						string += String.fromCharCode(ch);
				} else string += String.fromCharCode(ch);
				break;

			default:
				string += String.fromCharCode(ch);
			}
		}

		return DFMLComment.createWithContent(string);
	}

	/**
	 * Checks the character ch if alphabetic, '-', or '_'.
	 *
	 * @param {string} ch character to check.
	 * @return {boolean} true if ch is 'A'-'Z', 'a'-'z', '-' or '_'.
	 * @memberof DFMLParser
	 */
	isAlpha(ch) {
		if (ch === 45) return true; // -
		if (ch === 95) return true; // _
		if (/[a-zA-Z]/.test(String.fromCharCode(ch))) return true;
		return false;
	}

	/**
	 * Checks the character ch if alphanumeric, '-', or '_'.
	 *
	 * @param {string} ch character to check.
	 * @return {boolean} true if ch is 'A'-'Z', 'a'-'z', '0'-'9', '-' or '_'.
	 * @memberof DFMLParser
	 */
	isAlphaNum(ch) {
		if (/[0-9]/.test(String.fromCharCode(ch))) return true;
		return this.isAlpha(ch);
	}

	/**
	 * Checks if the provided character represents a number.
	 *
	 * @param {string} ch The ASCII value of the character to check.
	 * @return {boolean} True if the character represents a number, false otherwise.
	 * @memberof DFMLParser
	 */
	isNumber(ch) {
		if (ch === 45) return true;
		if (ch === 46) return true;
		if (/[0-9]/.test(String.fromCharCode(ch))) return true;

		return false;
	}
}
