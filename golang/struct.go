package main

import "fmt"

type Test struct {
	Name string
	Age  int
}

func main() {
	var t1 Test
	var t2 Test
	t1.Name = "Hoge"
	t1.Age = 32
	t2.Name = "Foo"
	t2.Age = 40
	fmt.Println([]Test{t1, t2})
}