package main

import (
	"flag"
	"fmt"

	"github.com/sukesan1984/snippets/blowfish-ecb/tool"
	"golang.org/x/crypto/blowfish"
)

var (
	strKey = flag.String("key", "", "the key")
	src    = flag.String("src", "", "the content")
)

func main() {
	flag.Parse()

	var hasError = false

	if strKey == nil || src == nil {
		fmt.Println("args error")
		hasError = true
	}

	block, err := blowfish.NewCipher([]byte(*strKey))

	if err != nil {
		fmt.Println("key error")
		hasError = true
	}

	if *src == "" {
		fmt.Println("plain content empty")
		hasError = true
	}

	if hasError {
		flag.Usage()
		return
	}

	source := fmt.Sprintf("%s", *src)
	encryptedContent := EncryptSrc(block, source)
	fmt.Println(encryptedContent)
}

func EncryptSrc(block *blowfish.Cipher, source string) []byte {
	content := []byte(source)
	content = tool.PKCS5Padding(content, block.BlockSize())

	ecb := tool.NewECBEncrypter(block)
	crypted := make([]byte, len(content))

	ecb.CryptBlocks(crypted, content)
	return crypted
}
