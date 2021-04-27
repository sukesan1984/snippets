package main

import (
	"fmt"
	"math/rand"
	"time"

	ulid "github.com/oklog/ulid/v2"
)

func genID() string {
	t := time.Now()
	entropy := ulid.Monotonic(rand.New(rand.NewSource(t.UnixNano())), 0)
	return ulid.MustNew(ulid.Timestamp(t), entropy).String()
}

func main() {
	fmt.Printf("ID: %s\n", genID())
}
