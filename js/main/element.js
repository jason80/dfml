

export class Element {
	constructor() {
		this.parent = null;
	}
  
	getParent() {
		return this.parent;
	}
  
	setParent(parent) {
		this.parent = parent;
	}
  
	getElementType() {
		throw new Error('getElementType() must be implemented by subclass');
	}

	static get NODE() {
		return 0;
	}
  
	static get DATA() {
		return 1;
	}
  
	static get COMMENT() {
		return 2;
	}
  }
