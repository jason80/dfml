
import { Builder } from "../main/builder.js";
import { Node } from "../main/node.js";
import { Data } from "../main/data.js"
import { Comment } from "../main/comment.js";


describe("Builder", function() {
	it("Node name", function() {
		const builder = Builder.create();
		const node = Node.create("test_node");
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

		const node = Node.create("test_node");
		node.addChild(Node.create("child1"));
		node.addChild(Node.create("child2"));
		node.addChild(Data.createString("string data"));
		node.addChild(Data.createInteger(20000));
		node.addChild(Data.createBoolean(false));
		node.addChild(Data.createDouble(3.149));

		const builder = Builder.create();
		expect(builder.buildNode(node)).toEqual(ss);
	});

	it("Node child's child", function() {

		let ss = "test_node {\n";
		ss += "\tchild1\n";
		ss += "\tchild2 {\n";
		ss += "\t\tchild3\n";
		ss += "\t}\n";
		ss += "}";

		const node = Node.create("test_node");
		const child1 = Node.create("child1"); node.addChild(child1);
		const child2 = Node.create("child2"); node.addChild(child2);
		child2.addChild(Node.create("child3"));

		const builder = Builder.create();
		expect(builder.buildNode(node)).toEqual(ss);
	});

	it("Data elements", function() {
		let data = Data.createString("hello");
		const builder = Builder.create();
		expect(builder.buildData(data)).toEqual("\"hello\"");

		data = Data.createInteger(20);
		expect(builder.buildData(data)).toEqual("20");

		data = Data.createDouble(3.14);
		expect(builder.buildData(data)).toEqual("3.14");

		data = Data.createBoolean(true);
		expect(builder.buildData(data)).toEqual("true");
	});

	it("Node attibutes", function() {
		const node = Node.create("person");
		node.setAttrString("name", "John");
		node.setAttrString("last", "Doe");
		node.setAttrInteger("ages", 40);
		node.setAttrDouble("height", 1.65);
		node.setAttrBoolean("single", true);

		const test =
			"person(name: \"John\", last: \"Doe\", ages: 40, height: 1.65, single: true)";

		const builder = Builder.create();
		expect(builder.buildNode(node)).toEqual(test);
	});

	it("Comments", function() {
		const node = Node.create("test_comments");
		node.addChild(Comment.createWithContent("comment 1"));
		node.addChild(Comment.createWithContent("comment 2"));

		const test =
		"test_comments {\n\t/*comment 1*/\n\t/*comment 2*/\n}";
		const builder = Builder.create();
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

		const animals = Node.create("animals");
		const bird = Node.create("bird");
		animals.addChild(bird);
			bird.addChild(Comment.createWithContent("A comment"));
			const duck = Node.create("duck");
			bird.addChild(duck);
			duck.setAttrBoolean("fly", true);
			duck.setAttrString("say", "qack");
			duck.setAttrString("name", "Donald");
				duck.addChild(Data.createInteger(20));
				duck.addChild(Data.createInteger(30));
				duck.addChild(Data.createInteger(40));
		const pet = Node.create("pet");
		animals.addChild(pet);
			const dog = Node.create("dog");
			pet.addChild(dog);
			dog.setAttrBoolean("fly", false);
			dog.setAttrString("say", "guau");
			dog.setAttrString("name", "Bob");
				dog.addChild(Data.createDouble(0.4));
				dog.addChild(Data.createBoolean(true));

		const builder = Builder.create();
		expect(builder.buildNode(animals)).toEqual(ss);
	});

	it("No format", function() {
		const test = "test_node { child1 child2 { child3 } }";

		const node = Node.create("test_node");
		let child = Node.create("child1"); node.addChild(child);
		child = Node.create("child2"); node.addChild(child);
		child.addChild(Node.create("child3"));

		const builder = Builder.create();
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

	const animals = Node.create("animals");
	const bird = Node.create("bird");
	animals.addChild(bird);
		bird.addChild(Comment.createWithContent("A comment"));
		const duck = Node.create("duck");
		bird.addChild(duck);
		duck.setAttrBoolean("fly", true);
		duck.setAttrString("say", "qack");
		duck.setAttrString("name", "Donald");
			duck.addChild(Data.createInteger(20));
			duck.addChild(Data.createInteger(30));
			duck.addChild(Data.createInteger(40));
	const pet = Node.create("pet");
	animals.addChild(pet);
		const dog = Node.create("dog");
		pet.addChild(dog);
		dog.setAttrBoolean("fly", false);
		dog.setAttrString("say", "guau");
		dog.setAttrString("name", "Bob");
			dog.addChild(Data.createDouble(0.4));
			dog.addChild(Data.createBoolean(true));

		const builder = Builder.create();

		builder.setFormat(true);
		builder.useSpacesForIndent(true);
		builder.setSpaceCount(3);

		expect(builder.buildNode(animals)).toEqual(ss);

	});

});
