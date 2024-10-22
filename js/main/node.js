import { DFMLElement } from "./element.js"
import { DFMLValue } from "./value.js"

export class DFMLNode extends DFMLElement {
	constructor() {
		super();
		this.name = '';
		this.attrs = new Map();
		this.keys = [];
		this.children = [];
	}

	static create(name) {
		const node = new DFMLNode();
		node.setName(name);
		return node;
	}

	setName(name) {
		this.name = name;
	}

	getName() {
		return this.name;
	}

	getElementType() {
		return DFMLElement.NODE;
	}

	addChild(element) {
		this.children.push(element);
		element.setParent(this);
	}

	setAttribute(name, value) {
		if (!this.hasAttr(name)) {
			this.keys.push(name);
		}
		this.attrs.set(name, value);
	}

	setAttrString(name, value) {
		const val = new DFMLValue();
		val.setString(value);
		this.setAttribute(name, val);
	}

	setAttrInteger(name, value) {
		const val = new DFMLValue();
		val.setInteger(value);
		this.setAttribute(name, val);
	}

	setAttrDouble(name, value) {
		const val = new DFMLValue();
		val.setDouble(value);
		this.setAttribute(name, val);
	}

	setAttrBoolean(name, value) {
		const val = new DFMLValue();
		val.setBoolean(value);
		this.setAttribute(name, val);
	}

	getAttr(name) {
		return this.attrs.get(name);
	}

	hasAttr(name) {
		return this.attrs.has(name);
	}

	getAttrKeys() {
		return this.keys;
	}

	getChildren() {
		return this.children;
	}
}
