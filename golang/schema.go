package main

import (
	"fmt"
	"net/url"

	"github.com/gorilla/schema"
)

var decoder = schema.NewDecoder()

type Person struct {
	Name  string `schema:"name,required"`
	Phone string `schema:"phone_number"`
}

func main() {
	q1 := url.Values{}
	q1.Add("name", "sukesan1984")
	p1 := &Person{}
	if err := decoder.Decode(p1, q1); err == nil {
		fmt.Printf("1. error does not occur.\n")
	}
}
