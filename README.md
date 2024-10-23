# Dragonfly Markup Language (DFML)

Dragonfly Markup Language (DFML) is a simple and versatile markup language designed to facilitate the structured representation of data. It provides a clear and readable syntax, ideal for various applications.

## Syntax example

```dfml
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

## Nodes

The nodes are main entities that can have attributes and can contain children.
The names of the nodes can be alphanumeric and include '_' and '-'. Ex:
```dfml
node1, node_4, _node_name, node-name
```

The names cannot start with a number or a '-', but they can start with a letter or '_'.

### Empty nodes

The following three examples are equivalent to each other:

```dfml
mynode
```

```dfml
mynode()
```

```dfml
mynode() {

}
```

### Node attributes

The attributes of a node are placed in parentheses following the name and are key-value pairs separated by commas. Example:

```dfml
bird(type: "Animal", fly: true, size: 20)
```

## Javascript testing: Jasmine:
https://github.com/jasmine/jasmine
