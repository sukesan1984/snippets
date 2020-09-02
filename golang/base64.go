// Copyright 2012 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Keep in sync with ../base32/example_test.go.

package main

import (
	"encoding/base64"
	"fmt"
	"os"
)

func Example() {
	//msg := "Hello, 世界"
	//encoded := base64.StdEncoding.EncodeToString([]byte(msg))
	//fmt.Println(encoded)
	encoded := "leOp2WdXDtp9Aia5odkMCsu6XmB/x2Rem6F0N7AevNTgGrca/e/VDRYWFiJFYQj9jPdeFF9AY3cjhaLIe9zgK13scdgG3MVDU9lg6WkL/BUATJpGZlLKUKnwvIonj2YN3AqVRlP/rjc2P3Kb9JToQyi9z2Dhex5cQ9HxjfnJeNbjJ15j+xzVnGji8CMWb2EHE14G199nxCVleUxvo8WI8Cy3hMdWrTA="
	decoded, err := base64.StdEncoding.DecodeString(encoded)
	if err != nil {
		fmt.Println("decode error:", err)
		return
	}
	fmt.Println(string(decoded))
	// Output:
	// SGVsbG8sIOS4lueVjA==
	// Hello, 世界
}

func ExampleEncoding_EncodeToString() {
	data := []byte("any + old & data")
	str := base64.StdEncoding.EncodeToString(data)
	fmt.Println(str)
	// Output:
	// YW55ICsgb2xkICYgZGF0YQ==
}

func ExampleEncoding_DecodeString() {
	str := "c29tZSBkYXRhIHdpdGggACBhbmQg77u/"
	data, err := base64.StdEncoding.DecodeString(str)
	if err != nil {
		fmt.Println("error:", err)
		return
	}
	fmt.Printf("%q\n", data)
	// Output:
	// "some data with \x00 and \ufeff"
}

func ExampleNewEncoder() {
	input := []byte("foo\x00bar")
	encoder := base64.NewEncoder(base64.StdEncoding, os.Stdout)
	encoder.Write(input)
	// Must close the encoder when finished to flush any partial blocks.
	// If you comment out the following line, the last partial block "r"
	// won't be encoded.
	encoder.Close()
	// Output:
	// Zm9vAGJhcg==
}

func main() {
	Example()
}
