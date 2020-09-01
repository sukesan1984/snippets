package main

import (
	"fmt"
	"reflect"
	"time"
)

func main() {
	minute := 60 * time.Minute
	fmt.Println(reflect.TypeOf(minute))
}
