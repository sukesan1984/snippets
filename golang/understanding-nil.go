package main

import "fmt"

type A struct {
	str string
}

func (a *A) example() string {
	return "example"
}

func main() {
	fn := (*A)(nil)
	fmt.Println(fn.example())
	fmt.Printf("%v: %T\n", fn, fn)
}
