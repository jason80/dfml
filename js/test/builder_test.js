
import { DFMLBuilder } from "../main/builder.js";
import { DFMLNode } from "../main/node.js";
import { DFMLData } from "../main/data.js"
import { DFMLComment } from "../main/comment.js";


describe("Builder", function() {
	it("Node name", function() {
		const builder = DFMLBuilder.create();
		const node = DFMLNode.create("test_node");
		expect(builder.buildNode(node)).toEqual("test_node");
	});

	it("Node childs", function() {
		let ss = "";

		ss += "test_node {\n";
		ss += "\tchild1\n";
		ss += "\tchild2\n";
		ss += "\t\"string data\"\n";
		ss += "\t" + 20000 + "\n";
		ss += "\t" + false + "\n";
		ss += "\t" + 3.149 + "\n";
		ss += "}";

		const node = DFMLNode.create("test_node");
		node.addChild(DFMLNode.create("child1"));
		node.addChild(DFMLNode.create("child2"));
		node.addChild(DFMLData.createString("string data"));
		node.addChild(DFMLData.createInteger(20000));
		node.addChild(DFMLData.createBoolean(false));
		node.addChild(DFMLData.createDouble(3.149));

		const builder = DFMLBuilder.create();
		expect(builder.buildNode(node)).toEqual(ss);
	});

	it("Node child's child", function() {

		let ss = "test_node {\n";
		ss += "\tchild1\n";
		ss += "\tchild2 {\n";
		ss += "\t\tchild3\n";
		ss += "\t}\n";
		ss += "}";

		const node = DFMLNode.create("test_node");
		const child1 = DFMLNode.create("child1"); node.addChild(child1);
		const child2 = DFMLNode.create("child2"); node.addChild(child2);
		child2.addChild(DFMLNode.create("child3"));

		const builder = DFMLBuilder.create();
		expect(builder.buildNode(node)).toEqual(ss);
	});

	it("Data elements", function() {
		let data = DFMLData.createString("hello");
		const builder = DFMLBuilder.create();
		expect(builder.buildData(data)).toEqual("\"hello\"");

		data = DFMLData.createInteger(20);
		expect(builder.buildData(data)).toEqual("20");

		data = DFMLData.createDouble(3.14);
		expect(builder.buildData(data)).toEqual("3.14");

		data = DFMLData.createBoolean(true);
		expect(builder.buildData(data)).toEqual("true");
	});

	it("Node attibutes", function() {
		const node = DFMLNode.create("person");
		node.setAttrString("name", "John");
		node.setAttrString("last", "Doe");
		node.setAttrInteger("ages", 40);
		node.setAttrDouble("height", 1.65);
		node.setAttrBoolean("single", true);

		const test =
			"person(name: \"John\", last: \"Doe\", ages: 40, height: 1.65, single: true)";

		const builder = DFMLBuilder.create();
		expect(builder.buildNode(node)).toEqual(test);
	});

	it("Comments", function() {
		const node = DFMLNode.create("test_comments");
		node.addChild(DFMLComment.createWithContent("comment 1"));
		node.addChild(DFMLComment.createWithContent("comment 2"));

		const test =
		"test_comments {\n\t/*comment 1*/\n\t/*comment 2*/\n}";
		const builder = DFMLBuilder.create();
		expect(builder.buildNode(node)).toEqual(test);
	});

	it("Combined", function() {
		let ss = "animals {\n";
		ss += "\tbird {\n";
		ss += "\t\t/*A comment*/\n";
		ss += "\t\tduck(fly: true, say: \"qack\", name: \"Donald\") {\n";
		ss += "\t\t\t20\n";
		ss += "\t\t\t30\n";
		ss += "\t\t\t40\n";
		ss += "\t\t}\n";
		ss += "\t}\n";
		ss += "\tpet {\n";
		ss += "\t\tdog(fly: false, say: \"guau\", name: \"Bob\") {\n";
		ss += "\t\t\t0.4\n";
		ss += "\t\t\ttrue\n";
		ss += "\t\t}\n";
		ss += "\t}\n";
		ss += "}";

		const animals = DFMLNode.create("animals");
		const bird = DFMLNode.create("bird");
		animals.addChild(bird);
			bird.addChild(DFMLComment.createWithContent("A comment"));
			const duck = DFMLNode.create("duck");
			bird.addChild(duck);
			duck.setAttrBoolean("fly", true);
			duck.setAttrString("say", "qack");
			duck.setAttrString("name", "Donald");
				duck.addChild(DFMLData.createInteger(20));
				duck.addChild(DFMLData.createInteger(30));
				duck.addChild(DFMLData.createInteger(40));
		const pet = DFMLNode.create("pet");
		animals.addChild(pet);
			const dog = DFMLNode.create("dog");
			pet.addChild(dog);
			dog.setAttrBoolean("fly", false);
			dog.setAttrString("say", "guau");
			dog.setAttrString("name", "Bob");
				dog.addChild(DFMLData.createDouble(0.4));
				dog.addChild(DFMLData.createBoolean(true));

		const builder = DFMLBuilder.create();
		expect(builder.buildNode(animals)).toEqual(ss);
	});

	it("No format", function() {
		const test = "test_node { child1 child2 { child3 } }";

		const node = DFMLNode.create("test_node");
		let child = DFMLNode.create("child1"); node.addChild(child);
		child = DFMLNode.create("child2"); node.addChild(child);
		child.addChild(DFMLNode.create("child3"));

		const builder = DFMLBuilder.create();
		builder.setFormat(false);

		expect(builder.buildNode(node)).toEqual(test);

	});

	it("Use spaces", function() {

		let ss = "animals {\n";
		ss += "   bird {\n";
			ss += "      /*A comment*/\n";
			ss += "      duck(fly: true, say: \"qack\", name: \"Donald\") {\n";
				ss += "         20\n";
				ss += "         30\n";
				ss += "         40\n";
			ss += "      }\n";
		ss += "   }\n";
		ss += "   pet {\n";
			ss += "      dog(fly: false, say: \"guau\", name: \"Bob\") {\n";
				ss += "         0.4\n";
				ss += "         true\n";
			ss += "      }\n";
		ss += "   }\n";
	ss += "}";

	const animals = DFMLNode.create("animals");
	const bird = DFMLNode.create("bird");
	animals.addChild(bird);
		bird.addChild(DFMLComment.createWithContent("A comment"));
		const duck = DFMLNode.create("duck");
		bird.addChild(duck);
		duck.setAttrBoolean("fly", true);
		duck.setAttrString("say", "qack");
		duck.setAttrString("name", "Donald");
			duck.addChild(DFMLData.createInteger(20));
			duck.addChild(DFMLData.createInteger(30));
			duck.addChild(DFMLData.createInteger(40));
	const pet = DFMLNode.create("pet");
	animals.addChild(pet);
		const dog = DFMLNode.create("dog");
		pet.addChild(dog);
		dog.setAttrBoolean("fly", false);
		dog.setAttrString("say", "guau");
		dog.setAttrString("name", "Bob");
			dog.addChild(DFMLData.createDouble(0.4));
			dog.addChild(DFMLData.createBoolean(true));

		const builder = DFMLBuilder.create();

		builder.setFormat(true);
		builder.useSpacesForIndent(true);
		builder.setSpaceCount(3);

		expect(builder.buildNode(animals)).toEqual(ss);

	});

});
