import { Element } from "./element.js"
import { Value } from "./value.js"

export class Node extends Element {
	constructor() {
		super();
		this.name = '';
		this.attrs = new Map();
		this.keys = [];
		this.children = [];
	}

	static create(name) {
		const node = new Node();
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
		return Element.NODE;
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
		const val = new Value();
		val.setString(value);
		this.setAttribute(name, val);
	}

	setAttrInteger(name, value) {
		const val = new Value();
		val.setInteger(value);
		this.setAttribute(name, val);
	}

	setAttrDouble(name, value) {
		const val = new Value();
		val.setDouble(value);
		this.setAttribute(name, val);
	}

	setAttrBoolean(name, value) {
		const val = new Value();
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
