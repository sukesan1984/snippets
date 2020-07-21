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

func main() {
	var m Message
	b := []byte(`{"Name":"Alice","Body":"Hello","Time":1294706395881547000}`)
	if err := json.Unmarshal(b, &m); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%s: %s\n", m.Name, m.Body)
}
