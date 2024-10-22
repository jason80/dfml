/**
 * Class representing a value in the Dragonfly Markup Language (DFML).
 *
 * @export
 * @class DFMLValue
 */
export class DFMLValue {

	/**
	 * Constant representing a string type value.
	 *
	 * @static
	 * @memberof DFMLValue
	 */
	static STRING = 0;

	/**
	 *Constant representing an integer type value.
	 *
	 * @static
	 * @memberof DFMLValue
	 */
	static INTEGER = 1;

	/**
	 * Constant representing a double type value.
	 *
	 * @static
	 * @memberof DFMLValue
	 */
	static DOUBLE = 2;

	/**
	 * Constant representing a boolean type value.
	 *
	 * @static
	 * @memberof DFMLValue
	 */
	static BOOLEAN = 3;

	/**
	 * Creates an instance of DFMLValue.
	 * @memberof DFMLValue
	 */
	constructor() {
		this.type = null;
		this.value = '';
	}

	/**
	 * Sets the value as a string.
	 *
	 * @param {string} data he string data to set.
	 * @memberof DFMLValue
	 */
	setString(data) {
		this.type = DFMLValue.STRING;
		this.value = data;
	}

	/**
	 * Sets the value as an integer.
	 *
	 * @param {number} data
	 * @memberof DFMLValue The integer data to set.
	 */
	setInteger(data) {
		this.type = DFMLValue.INTEGER;
		this.value = data.toString();
	}

	/**
	 * Sets the value as a double.
	 *
	 * @param {number} data The double data to set.
	 * @memberof DFMLValue
	 */
	setDouble(data) {
		this.type = DFMLValue.DOUBLE;
		this.value = data.toString();
	}

	/**
	 * Sets the value as a boolean.
	 *
	 * @param {boolean} data The boolean data to set.
	 * @memberof DFMLValue
	 */
	setBoolean(data) {
		this.type = DFMLValue.BOOLEAN;
		this.value = data ? "true" : "false";
	}

	/**
	 * Gets the type of the value.
	 *
	 * @return {number} The type of the value.
	 * @memberof DFMLValue
	 */
	getType() {
		return this.type;
	}

	/**
	 * Gets the string representation of the value.
	 *
	 * @return {string} The string representation of the value.
	 * @memberof DFMLValue
	 */
	getValue() {
		return this.value;
	}
}
