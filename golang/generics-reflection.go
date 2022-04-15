package main

import (
	"fmt"
	"reflect"
)

type AStruct struct {
	A int
	B int
	C string
	D float32
}

type BStruct struct {
	A int
	B int
	C string
}

type CStruct struct {
	A int
	B int
}

func main() {
	a := &AStruct{
		A: 1,
		B: 2,
		C: "hoge",
		D: 3.2,
	}
	b := convert[BStruct](a)
	c := convert[CStruct](a)
	fmt.Println("==b==")
	fmt.Println(b)
	fmt.Println("==c==")
	fmt.Println(c)
}

func convert[T any](a *AStruct) T {
	var s T
	tv := reflect.TypeOf(s)
	sp := reflect.ValueOf(&s)
	se := sp.Elem()

	ap := reflect.ValueOf(a)
	ae := ap.Elem()
	for i := 0; i < tv.NumField(); i++ {
		t := tv.Field(i)
		//fmt.Println("Name:", t.Name, "type:", t.Type)
		//fmt.Println("a:", ae.FieldByName(t.Name))
		se.FieldByName(t.Name).Set(ae.FieldByName(t.Name))
	}

	return s
}
