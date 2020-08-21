package main

import (
	"fmt"
	"io/ioutil"
	"os"

	"github.com/dgrijalva/jwt-go"
)

func validate(tokenString string) {

	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
		if _, ok := token.Method.(*jwt.SigningMethodRSA); !ok {
			return nil, fmt.Errorf("Unexpected signing method: %v", token.Header["alg"])
		}
		verifyBytes, err := ioutil.ReadFile("./key.pem.pub.pkcs8")
		if err != nil {
			panic(err)
		}
		return jwt.ParseRSAPublicKeyFromPEM(verifyBytes)
	})
	//if err != nil {
	//	panic(err)
	//}

	if claims, ok := token.Claims.(jwt.MapClaims); ok && token.Valid {
		fmt.Println(claims["foo"], claims["nbf"])
	} else {
		fmt.Println(err)
	}
}

func main() {
	validate(os.Args[1])
}
