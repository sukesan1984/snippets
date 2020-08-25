package main

import (
	"fmt"
	"io/ioutil"
	"time"

	"github.com/dgrijalva/jwt-go"
)

const (
	iatKey   = "iat"
	expKey   = "exp"
	lifetime = 1 * time.Minute
)

func sign() (string, error) {
	signBytes, err := ioutil.ReadFile("./key.pem")
	if err != nil {
		panic(err)
	}
	signKey, err := jwt.ParseRSAPrivateKeyFromPEM(signBytes)
	if err != nil {
		panic(err)
	}
	now := time.Now()
	token := jwt.NewWithClaims(jwt.SigningMethodRS256, jwt.MapClaims{
		iatKey: now.Unix(),
		expKey: now.Add(lifetime).Unix(),
		"foo":  "bar",
		"nbf":  time.Date(2015, 10, 10, 12, 0, 0, 0, time.UTC).Unix(),
	})
	return token.SignedString(signKey)
}

func main() {
	tokenString, _ := sign()
	fmt.Println(tokenString)
}
