package main

import (
	"fmt"
	"regexp"
)

func main() {
	m := "クレジットカード0000 0000 0000-••••"
	var reP = regexp.MustCompile(`[-.•\d\s ]+$`)
	fmt.Println(reP.ReplaceAllString(m, ""))
}
