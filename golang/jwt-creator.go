package main

import (
	"fmt"
	"time"

	"github.com/dgrijalva/jwt-go"
)

func sign() (string, error) {
	//token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
	token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
		"foo": "bar",
		"nbf": time.Date(2015, 10, 10, 12, 0, 0, 0, time.UTC).Unix(),
	})

	return token.SignedString(hmacSampleSecret)
}

var hmacSampleSecret = []byte("my_secret_ley")

func main() {
	tokenString, _ := sign()
	fmt.Println(tokenString)
}
