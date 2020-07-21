package main

import (
	"encoding/json"
	"fmt"
	"log"
)

type Message struct {
	Name string
	Body string
	Time int64
}

var str string = `{
	"Name":"Alice",
	"Body":"Hello",
	"Time":1294706395881547000
	}`

func main() {
	var m Message
	b := []byte(str)
	if err := json.Unmarshal(b, &m); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%s: %s\n", m.Name, m.Body)
}
