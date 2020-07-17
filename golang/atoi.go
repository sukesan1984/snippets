package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	v32_max := "2147483647"
	v32_min := "-2147483648"
	v64_max := "9223372036854775807"
	v64_min := "-9223372036854775808"
	fmt.Println("Atoi")
	if s, err := strconv.Atoi(v32_max); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	}
	if s, err := strconv.Atoi(v32_min); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	}
	if s, err := strconv.Atoi(v64_max); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	}
	if s, err := strconv.Atoi(v64_min); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	}

	fmt.Println("ParseInt_32")
	if s, err := strconv.ParseInt(v64_max, 10, 32); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	} else {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}

	if s, err := strconv.ParseInt(v64_min, 10, 32); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	} else {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}

	fmt.Println("ParseInt_64")
	if s, err := strconv.ParseInt(v64_max, 10, 64); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	} else {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}

	if s, err := strconv.ParseInt(v64_min, 10, 64); err == nil {
		fmt.Printf("%T, %v\n", s, s)
	} else {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}
}
