export class Value {
	static STRING = 0;
	static INTEGER = 1;
	static DOUBLE = 2;
	static BOOLEAN = 3;

	constructor() {
		this.type = null;
		this.value = '';
	}

	setString(data) {
		this.type = Value.STRING;
		this.value = data;
	}

	setInteger(data) {
		this.type = Value.INTEGER;
		this.value = data.toString();
	}

	setDouble(data) {
		this.type = Value.DOUBLE;
		this.value = data.toString();
	}

	setBoolean(data) {
		this.type = Value.BOOLEAN;
		this.value = data ? "true" : "false";
	}

	getType() {
		return this.type;
	}

	getValue() {
		return this.value;
	}
}
