import { Element } from "./element.js"

export class Comment extends Element {
	constructor(content = "") {
		super();
		this.content = content;
	}
  
	static create() {
		return new Comment();
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
		return Element.COMMENT;
	}
  }
