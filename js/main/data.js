import { DFMLElement } from "./element.js"
import { DFMLValue } from "./value.js";

export class DFMLData extends DFMLElement {
	constructor(value) {
		super()
		this.value = value;
	}

	static create() {
		return new DFMLData(new DFMLValue());
	}

	static createWithValue(value) {
		return new DFMLData(value);
	}

	static createString(value) {
		const val = new DFMLValue();
		val.setString(value);
		return new DFMLData(val);
	}

	static createInteger(value) {
		const val = new DFMLValue();
		val.setInteger(value);
		return new DFMLData(val);
	}

	static createDouble(value) {
		const val = new DFMLValue();
		val.setDouble(value);
		return new DFMLData(val);
	}

	static createBoolean(value) {
		const val = new DFMLValue();
		val.setBoolean(value);
		return new DFMLData(val);
	}

	getElementType() {
		return DFMLElement.DATA
	}

	getValue() {
		return this.value;
	}
}
