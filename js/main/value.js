export class DFMLValue {
	static STRING = 0;
	static INTEGER = 1;
	static DOUBLE = 2;
	static BOOLEAN = 3;

	constructor() {
		this.type = null;
		this.value = '';
	}

	setString(data) {
		this.type = DFMLValue.STRING;
		this.value = data;
	}

	setInteger(data) {
		this.type = DFMLValue.INTEGER;
		this.value = data.toString();
	}

	setDouble(data) {
		this.type = DFMLValue.DOUBLE;
		this.value = data.toString();
	}

	setBoolean(data) {
		this.type = DFMLValue.BOOLEAN;
		this.value = data ? "true" : "false";
	}

	getType() {
		return this.type;
	}

	getValue() {
		return this.value;
	}
}
