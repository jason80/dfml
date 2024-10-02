import { Parser } from "../main/parser.js";
import { Element } from "../main/element.js";
import { Value } from "../main/value.js";
import { Builder } from "../main/builder.js";

describe("Parser", function() {

	it("Single node", function() {
		const test = "test";
		const parser = Parser.create(test);
		const list = parser.parse();

		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.NODE);
		expect(list[0].getName()).toEqual("test");
	});

	it("Child nodes", function() {
		const string =  "red   {     green     blue   {  yellow  }  }  ";
		const parser = Parser.create(string);
		const list = parser.parse();

		expect(list.length).toEqual(1);

		expect(list[0].getElementType()).toEqual(Element.NODE);
		expect(list[0].getName()).toEqual("red");

		expect(list[0].getChildren().length).toEqual(2);

		const test = list[0];
		expect(test.getChildren()[0].getElementType()).toEqual(Element.NODE);
		expect(test.getChildren()[1].getElementType()).toEqual(Element.NODE);

		const test1 = test.getChildren()[0];
		const test2 = test.getChildren()[1];

		expect(test1.getName()).toEqual("green");
		expect(test2.getName()).toEqual("blue");

		expect(test1.getChildren().length).toEqual(0);
		expect(test2.getChildren().length).toEqual(1);

		expect(test2.getChildren()[0].getName()).toEqual("yellow");
	});

	it("Parse data", function() {
		const string = "'hello' \"HELLO\" 23 5.67 true";

		const parser = Parser.create(string);
		const list = parser.parse();

		expect(list.length).toEqual(5);

		list.forEach((e) => {
			expect(e.getElementType()).toEqual(Element.DATA);
		});

		expect(list[0].getValue().getType()).toEqual(Value.STRING);
		expect(list[0].getValue().getValue()).toEqual("hello");

		expect(list[1].getValue().getType()).toEqual(Value.STRING);
		expect(list[1].getValue().getValue()).toEqual("HELLO");

		expect(list[2].getValue().getType()).toEqual(Value.INTEGER);
		expect(list[2].getValue().getValue()).toEqual("23");

		expect(list[3].getValue().getType()).toEqual(Value.DOUBLE);
		expect(list[3].getValue().getValue()).toEqual("5.67");

		expect(list[4].getValue().getType()).toEqual(Value.BOOLEAN);
		expect(list[4].getValue().getValue()).toEqual("true");
	});

	it("Single string value", function() {
		const parser = Parser.create("'single string'");
		const list = parser.parse();

		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.DATA);
		expect(list[0].getValue().getType()).toEqual(Value.STRING);
		expect(list[0].getValue().getValue()).toEqual('single string');
	});

	it("Single integer value", function() {
		const parser = Parser.create("1234");
		const list = parser.parse();

		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.DATA);
		expect(list[0].getValue().getType()).toEqual(Value.INTEGER);
		expect(list[0].getValue().getValue()).toEqual('1234');
	});

	it("Single double value", function() {
		const parser = Parser.create("1234.46");
		const list = parser.parse();

		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.DATA);
		expect(list[0].getValue().getType()).toEqual(Value.DOUBLE);
		expect(list[0].getValue().getValue()).toEqual('1234.46');
	});

	it("Single boolean value", function() {
		const parser = Parser.create("false");
		const list = parser.parse();

		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.DATA);
		expect(list[0].getValue().getType()).toEqual(Value.BOOLEAN);
		expect(list[0].getValue().getValue()).toEqual('false');
	});

	it("Attributes: parse empty", function() {
		const parser = Parser.create("mynode()");
		const list = parser.parse();

		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.NODE);
		expect(list[0].getName()).toEqual("mynode");
		expect(list[0].getAttrKeys().length).toEqual(0);
	});

	it("Attributes: parse single", function() {
		const parser = Parser.create("mynode(test: 'hello')");
		const list = parser.parse();

		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.NODE);
		expect(list[0].getName()).toEqual("mynode");
		expect(list[0].getAttrKeys().length).toEqual(1);
		expect(list[0].hasAttr("test")).toEqual(true);
		expect(list[0].getAttr("test").getValue()).toEqual("hello");
	});

	it("Attributes: parse combined", function() {
		const parser = Parser.create(
			"mynode(test: 'hello', number: 40, boolean: false)");
		const list = parser.parse();
		expect(list.length).toEqual(1);
		expect(list[0].getElementType()).toEqual(Element.NODE);
		expect(list[0].getName()).toEqual("mynode");
		expect(list[0].getAttrKeys().length).toEqual(3);

		expect(list[0].getAttr("test").getType()).toEqual(Value.STRING);
		expect(list[0].getAttr("test").getValue()).toEqual("hello");

		expect(list[0].getAttr("number").getType()).toEqual(Value.INTEGER);
		expect(list[0].getAttr("number").getValue()).toEqual("40");

		expect(list[0].getAttr("boolean").getType()).toEqual(Value.BOOLEAN);
		expect(list[0].getAttr("boolean").getValue()).toEqual("false");
	});

	it("Comments: single", function() {
		const parser = Parser.create(
			"/*Hello\nWorld*/\n#Single comment\n//Another single"
		);

		const list = parser.parse();
		expect(list.length).toEqual(3);

		expect(list[0].getElementType()).toEqual(Element.COMMENT);
		expect(list[0].getString()).toEqual("Hello\nWorld");

		expect(list[1].getElementType()).toEqual(Element.COMMENT);
		expect(list[1].getString()).toEqual("Single comment");

		expect(list[2].getElementType()).toEqual(Element.COMMENT);
		expect(list[2].getString()).toEqual("Another single");
	});

	it("Parse file", function(done) {
		let parsing = "";
		let parsed = "";
	
		fetch('parsing.dfml')
			.then(response => {
				if (!response.ok) {
					throw new Error('Loading parsing.dfml');
				}
				return response.text();
			})
			.then(data => {
				parsing = data;
				return fetch('parsed.dfml');
			})
			.then(response => {
				if (!response.ok) {
					throw new Error('Loading parsed.dfml');
				}
				return response.text();
			})
			.then(data => {
				parsed = data;
	
				const parser = Parser.create(parsing);
				const list = parser.parse();
				const builder = Builder.create();
	
				const result = builder.buildNode(list[0]) + "\n";

				expect(result).toEqual(parsed);
				done(); // call 'done' to finish
			})
			.catch(error => {
				console.error(error);
				done.fail(error);
			});
	});

	it("Doubles", function(done) {
		fetch('doubles.dfml')
			.then(response => {
				if (!response.ok) {
					throw new Error('Loading doubles.dfml');
				}
				return response.text();
			})
			.then(doubles => {
				const parser = Parser.create(doubles);
				const list = parser.parse();
	
				expect(list.length).toEqual(2);
	
				expect(list[0].getElementType()).toEqual(Element.NODE);
				expect(list[0].getName()).toEqual("doubleset");
	
				expect(list[0].getAttrKeys().length).toEqual(3);
	
				expect(list[0].getAttr("double1").getType()).toEqual(Value.DOUBLE);
				expect(list[0].getAttr("double1").getValue()).toEqual("30.3");
	
				expect(list[0].getAttr("double2").getType()).toEqual(Value.DOUBLE);
				expect(list[0].getAttr("double2").getValue()).toEqual("3.14");
	
				expect(list[0].getAttr("double3").getType()).toEqual(Value.DOUBLE);
				expect(list[0].getAttr("double3").getValue()).toEqual("0.0023");
	
				expect(list[1].getElementType()).toEqual(Element.NODE);
				expect(list[1].getName()).toEqual("otherset");
	
				expect(list[1].getAttr("float1").getValue()).toEqual("456.21");
	
				expect(list[1].getAttr("float2").getType()).toEqual(Value.DOUBLE);
				expect(list[1].getAttr("float2").getValue()).toEqual("2");
	
				const nested = list[1].getChildren()[0];
				expect(nested.getAttr("size").getType()).toEqual(Value.DOUBLE);
				expect(nested.getAttr("size").getValue()).toEqual("200.5");
	
				done();
			})
			.catch(error => {
				console.error("Error:", error);
				done.fail(error);
			});
	});
	
});
