package main

import (
	"fmt"

	"github.com/go-playground/validator"
)

type User struct {
	Email    string `json:"email" validate:"required,email"`
	Name     string `json:"name" validate:"required"`
	Nickname string `json:"nickname"`
}

func main() {
	v := validator.New()
	u := User{}
	err := v.Struct(u)

	for _, e := range err.(validator.ValidationErrors) {
		fmt.Println(e)
	}

	u = User{
		Email: "hoge@example.com",
		Name:  "sukesan1984",
	}

	if err = v.Struct(u); err != nil {
		for _, e := range err.(validator.ValidationErrors) {
			fmt.Println(e)
		}
	} else {
		fmt.Printf("valid: %v", u )
	}
}
