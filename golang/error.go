package main

import (
	"fmt"

	"github.com/pkg/errors"
)

func main() {
	cause := errors.New("Whoops")
	err := errors.WithStack(cause)
	fmt.Printf("%+v", err)
}
