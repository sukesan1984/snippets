package main

import "fmt"

const (
	Hoge = 10
	Fuga = 12
)

func main() {
	i := 11
	switch i {
	case Hoge:
		fmt.Println("Hoge")
	case Fuga:
		fmt.Println("Fuga")
	default:
		fmt.Println("Other")
	}
}
