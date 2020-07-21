package main

import "fmt"

func main() {
	i := 4
	j := 5
	k := 6
	ary := []int{1, 2, 3}
	var aryPointer *[]int
	pointerAry := []*int{&i, &j, &k}
	fmt.Println(ary)
	aryPointer = &ary
	fmt.Println(*aryPointer)
	for _, i := range pointerAry {
		fmt.Println(*i)
	}
}
