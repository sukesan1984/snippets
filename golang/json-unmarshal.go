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
var strAry string = `[{
	"Name":"Alice",
	"Body":"Hello",
	"Time":1294706395881547000
	}]`

func main() {
	var m Message
	var ma []Message
	b := []byte(str)
	if err := json.Unmarshal(b, &m); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%s: %s\n", m.Name, m.Body)

	if err := json.Unmarshal([]byte(strAry), &ma); err != nil {
		log.Fatal(err)
	}
	fmt.Println(ma)
	for _, i := range ma {
		fmt.Printf("%s: %s\n", i.Name, i.Body)
	}
}
