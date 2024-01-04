# Dragonfly Markup Language (DML)

Dragonfly Markup Language (DML) is a simple and versatile markup language designed to facilitate the structured representation of data. It provides a clear and readable syntax, ideal for various applications.

## Syntax example

```dml
node (name: "my node", number: 38, attribute_only) {
	"a string"
    20
    3.14
	child_node (key: "child of the node") {
		empty_node
		empty_node2()
	}
}
```
