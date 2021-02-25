package main

import (
	"fmt"
	"sort"
	"strconv"
	"strings"
)

type Number []string

func (n Number) Len() int {
	return len(n)
}

func (n Number) Swap(i, j int) {
	n[i], n[j] = n[j], n[i]
}

func (n Number) Less(i, j int) bool {
	a := strings.Split(n[i], ".")
	b := strings.Split(n[j], ".")
	aLen := len(a)
	bLen := len(b)
	var min int
	if aLen < bLen {
		min = aLen
	} else {
		min = bLen
	}
	for k := 0; k < min; k++ {
		ai, err := strconv.ParseInt(a[k], 10, 32)
		if err != nil {
			panic(err)
		}
		bi, err := strconv.ParseInt(b[k], 10, 32)
		if err != nil {
			panic(err)
		}

		if ai != bi {
			return ai < bi
		}
	}
	if (min == aLen) {
		return true
	}
	return false
}

func main() {
	array := Number{"1.0.0", "2.1.1", "2.1", "1.0.1", "1.2.2", "3", "1.1", "1.1.2", "2.2.1", "2.3"}
	sort.Sort(array)
	fmt.Println(array)
}
