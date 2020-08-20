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

type Number struct {
	Num *int64
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
	},{
	"Name":"Bob",
	"Body":"Goodbye"
	}]`

var str2Ary string = `[{
	"Num": 1
	},{
	}]`

func main() {
	var m Message
	var ma []Message
	b := []byte(str)
	if err := json.Unmarshal(b, &m); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%s: %s, %d\n", m.Name, m.Body, m.Time)

	if err := json.Unmarshal([]byte(strAry), &ma); err != nil {
		log.Fatal(err)
	}
	fmt.Println(ma)
	for _, i := range ma {
		fmt.Printf("%s: %s, %d\n", i.Name, i.Body, i.Time)
	}

	var na []Number
	if err := json.Unmarshal([]byte(str2Ary), &na); err != nil {
		log.Fatal(err)
	}
	for _, i := range na {
		fmt.Printf("num: %d\n", i.Num)
	}
}
