import { DFMLElement } from "./element.js"
import { DFMLValue } from "./value.js";

/**
 * Class representing a data element in the Dragonfly Markup Language (DFML).
 *
 * @export
 * @class DFMLData
 * @extends {DFMLElement}
 */
export class DFMLData extends DFMLElement {
	/**
	 * Creates an instance of DFMLData.
	 * @param {DFMLValue} value the value of the data.
	 * @memberof DFMLData
	 */
	constructor(value) {
		super()
		this.value = value;
	}

	/**
	 * Creates and returns an empty DFMLData instance.
	 *
	 * @static
	 * @return {DFMLData} the new DFMLData instance.
	 * @memberof DFMLData
	 */
	static create() {
		return new DFMLData(new DFMLValue());
	}

	/**
	 * Creates and returns a DFMLData instance with the given value.
	 *
	 * @static
	 * @param {DFMLValue} value the value object.
	 * @return {DFMLData} the new DFMLData instance.
	 * @memberof DFMLData
	 */
	static createWithValue(value) {
		return new DFMLData(value);
	}

	/**
	 * Creates and returns a DFMLData instance with the specified string value.
	 *
	 * @static
	 * @param {string} value The string value of the data.
	 * @return {DFMLData} the new Data instance.
	 * @memberof DFMLData
	 */
	static createString(value) {
		const val = new DFMLValue();
		val.setString(value);
		return new DFMLData(val);
	}

	/**
	 * Creates and returns a DFMLData instance with the specified integer value.
	 *
	 * @static
	 * @param {number} value The integer value of the data.
	 * @return {DFMLData} the new Data instance.
	 * @memberof DFMLData
	 */
	static createInteger(value) {
		const val = new DFMLValue();
		val.setInteger(value);
		return new DFMLData(val);
	}

	/**
	 * Creates and returns a DFMLData instance with the specified double value.
	 *
	 * @static
	 * @param {number} value The double value of the data.
	 * @return {DFMLData} the new Data instance.
	 * @memberof DFMLData
	 */
	static createDouble(value) {
		const val = new DFMLValue();
		val.setDouble(value);
		return new DFMLData(val);
	}

	/**
	 * Creates and returns a DFMLData instance with the specified boolean value.
	 *
	 * @static
	 * @param {boolean} value The boolean value of the data.
	 * @return {DFMLData} the new Data instance.
	 * @memberof DFMLData
	 */
	static createBoolean(value) {
		const val = new DFMLValue();
		val.setBoolean(value);
		return new DFMLData(val);
	}

	/**
	 * Gets the element type as an integer, identifying it as data.
	 *
	 * @return {number} The element type (DATA).
	 * @memberof DFMLData
	 */
	getElementType() {
		return DFMLElement.DATA
	}

	/**
	 * Gets the value object associated with the data.
	 *
	 * @return {DFMLValue} the value object.
	 * @memberof DFMLData
	 */
	getValue() {
		return this.value;
	}
}
