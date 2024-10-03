import { Node } from "./node.js"
import { Data } from "./data.js"
import { Value } from "./value.js";
import { Comment } from "./comment.js"

class ParserException extends Error {
	constructor(message) {
		super(message);
		this.name = "ParserException";
	}
}

class CharIterator {
	constructor(data = '') {
		this.data = data;
		this.i = 0;
		this.line = 1;
	}

	setData(data) {
		this.data = data;
		this.i = 0;
		this.line = 1;
	}

	next() {
		if (this.i >= this.data.length) return -1;
		const ch = this.data[this.i++];
		if (ch === '\n') this.line++;
		return ch.charCodeAt(0);
	}

	current() {
		return this.data[this.i - 1];
	}

	back() {
		this.i--;
	}

	end() {
		return this.i >= this.data.length;
	}

	getLine() {
		return this.line.toString();
	}
}

export class Parser {
	constructor(data) {
		this.i = new CharIterator(data);
	}

	static create(data) {
		return new Parser(data);
	}

	parse() {
		const list = [];
		this.parseChildren(list);
		return list;
	}

	parseChildren(childs) {
		let ch;
		let value = new Value();
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
					value = new Value();
					this.parseString(value);
					childs.push(Data.createWithValue(value));
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
						value = new Value();
						this.parseNumber(value);
						childs.push(Data.createWithValue(value));
					} else {
						throw new ParserException("Invalid character for node child on line: " + this.i.getLine());
					}
			}
		}
	}

	parseNode() {
		let ch;
		const name = this.parseNodeName();

		if (name === "true") return Data.createBoolean(true);
		if (name === "false") return Data.createBoolean(false);

		const node = Node.create(name);
		let children = [];

		if (this.i.end()) return node;

		this.i.back();

		if (!node.name) {
			throw new ParserException("Empty node name encountered on line: " + this.i.getLine());
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
						throw new ParserException("Double attribute list found in the node on line: " + this.i.getLine());
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

	parseNodeAttribute(node) {
		let key = '';
		let value = new Value();
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
			throw new ParserException("Boolean conversion error on line: " + this.i.getLine());
		}
	}

	parseComment() {
		let ch = this.i.next();
		let singleLine = false;
		let string = '';

		if (ch === 35) // #
			singleLine = true;
		else if (ch === 47) { // /
			ch = this.i.next();
			if (ch === -1)
				throw new ParserException("Unexpected comment termination on line: " + this.i.getLine());
			else if (ch === 47) // /
				singleLine = true;
			else if (ch === 42) // *
				singleLine = false;
			else {
				throw new ParserException("Unexpected comment termination on line: " + this.i.getLine());
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

		return Comment.createWithContent(string);
	}

	isAlpha(ch) {
		if (ch === 45) return true; // -
		if (ch === 95) return true; // _
		if (/[a-zA-Z]/.test(String.fromCharCode(ch))) return true;
		return false;
	}

	isAlphaNum(ch) {
		if (/[0-9]/.test(String.fromCharCode(ch))) return true;
		return this.isAlpha(ch);
	}

	isNumber(ch) {
		if (ch === 45) return true;
		if (ch === 46) return true;
		if (/[0-9]/.test(String.fromCharCode(ch))) return true;

		return false;
	}
}
