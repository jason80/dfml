import { Node } from "./node.js";
import { Value } from "./value.js";
import { Comment } from "./comment.js";
import { Data } from "./data.js";

export class Builder {
	constructor() {
	  this.level = 0;
	  this.format = true;      // Habilitar formato (indentación y saltos de línea)
	  this.useSpaces = false;  // Usar espacios para la indentación
	  this.spaceCount = 4;     // Número de espacios para la indentación
	}
  
	static create() {
	  return new Builder();
	}
  
	setFormat(f) {
	  this.format = f;
	}
  
	useSpacesForIndent(us) {
	  this.useSpaces = us;
	}
  
	setSpaceCount(count) {
	  this.spaceCount = count;
	}
  
	buildNode(node) {
	  let result = this.indent() + node.getName();
  
	  if (node.getAttrKeys().length > 0) {
		result += this.buildAttributes(node);
	  }
  
	  const children = node.getChildren();
	  if (children.length > 0) {
		result += this.format ? " {\n" : " { ";
		this.level++;
		children.forEach(child => {
		  result += this.buildElement(child) + (this.format ? "\n" : " ");
		});
		this.level--;
		result += this.indent() + "}";
	  }
  
	  return result;
	}

	buildElement(element) {
		if (element instanceof Node) {
			return this.buildNode(element);
		} else if (element instanceof Data) {
			return this.buildData(element);
		} else if (element instanceof Comment) {
			return this.buildComment(element);
		} else {
			throw new Error("Unrecognized element type.");
		}
	}
  
	/**
	 * @brief Genera la representación DFML de un dato.
	 * 
	 * @param {Data} data - El dato a construir.
	 * @return {string} La representación DFML del dato.
	 */
	buildData(data) {
	  return this.indent() + this.buildValue(data.getValue());
	}
  
	/**
	 * @brief Genera la representación DFML de un comentario.
	 * 
	 * @param {Comment} comment - El comentario a construir.
	 * @return {string} La representación DFML del comentario.
	 */
	buildComment(comment) {
	  return this.indent() + `/*${comment.getString()}*/`;
	}
  
	/**
	 * @brief Genera la representación DFML de un valor.
	 * 
	 * @param {Value} value - El valor a construir.
	 * @return {string} La representación DFML del valor.
	 */
	buildValue(value) {
	  if (value.getType() === Value.STRING) {
		return `"${value.getValue()}"`;
	  } else {
		return value.getValue();
	  }
	}
  
	/**
	 * @brief Genera la representación DFML de los atributos de un nodo.
	 * 
	 * @param {Node} node - El nodo del que construir los atributos.
	 * @return {string} La representación DFML de los atributos del nodo.
	 */
	buildAttributes(node) {
	  const attrs = node.getAttrKeys().map(key => {
		return `${key}: ${this.buildValue(node.getAttr(key))}`;
	  }).join(', ');
  
	  return `(${attrs})`;
	}
  
	/**
	 * @brief Obtiene la indentación actual basada en el nivel del constructor.
	 * 
	 * @return {string} La cadena de espacios o tabulaciones para la indentación.
	 */
	indent() {
	  if (!this.format || this.level === 0) return '';
  
	  const indentString = this.useSpaces ? ' '.repeat(this.spaceCount) : '\t';
	  return indentString.repeat(this.level);
	}
  }
  