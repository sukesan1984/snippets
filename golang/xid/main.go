package main

import (
	"fmt"

	"github.com/rs/xid"
)

func main() {
	guid := xid.New()
	fmt.Println(guid.String())
}
