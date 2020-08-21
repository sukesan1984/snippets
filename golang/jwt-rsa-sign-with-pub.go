package main

import (
	"fmt"
	"io/ioutil"
	"time"

	"github.com/dgrijalva/jwt-go"
)

func sign() (string, error) {
	hmacSampleSecret, err := ioutil.ReadFile("./key.pem.pub.pkcs8")
	if err != nil {
		panic(err)
	}
	//token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
	token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
		"foo": "bar",
		"nbf": time.Date(2015, 10, 10, 12, 0, 0, 0, time.UTC).Unix(),
	})

	return token.SignedString(hmacSampleSecret)
}

func main() {
	tokenString, _ := sign()
	fmt.Println(tokenString)
}
