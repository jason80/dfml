import { Element } from "./element.js"
import { Value } from "./value.js";

export class Data extends Element {
	constructor(value) {
		super()
		this.value = value;
	}

	static create() {
		return new Data(new Value());
	}

	static createWithValue(value) {
		return new Data(value);
	}

	static createString(value) {
		const val = new Value();
		val.setString(value);
		return new Data(val);
	}

	static createInteger(value) {
		const val = new Value();
		val.setInteger(value);
		return new Data(val);
	}

	static createDouble(value) {
		const val = new Value();
		val.setDouble(value);
		return new Data(val);
	}

	static createBoolean(value) {
		const val = new Value();
		val.setBoolean(value);
		return new Data(val);
	}

	getElementType() {
		return Element.DATA
	}

	getValue() {
		return this.value;
	}
}
