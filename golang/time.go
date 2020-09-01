package main

import (
	"fmt"
	"reflect"
	"time"
)

func main() {
	var seconds int64
	seconds = 10
	minute := 60 * time.Minute
	fmt.Println(reflect.TypeOf(minute))
	fmt.Println(time.Duration(seconds) * time.Second)
}
