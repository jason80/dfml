import { DFMLElement } from "./element.js"

export class DFMLComment extends DFMLElement {
	constructor(content = "") {
		super();
		this.content = content;
	}
  
	static create() {
		return new DFMLComment();
	}
  
	static createWithContent(content) {
		const comment = this.create(); 
		comment.setString(content); 
		return comment; 
	}
  
	setString(content) {
		this.content = content;
	}
  
	getString() {
		return this.content;
	}
  
	getElementType() {
		return DFMLElement.COMMENT;
	}
  }
