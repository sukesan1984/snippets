package main

import (
	"bytes"
	"fmt"
	"log"
	"os"

	"github.com/google/go-cmp/cmp"
)

func useFileRead(fileName string) []byte {
	fp, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer fp.Close()

	buf := make([]byte, 244)
	for {
		n, err := fp.Read(buf)
		if n == 0 {
			break
		}
		if err != nil {
			log.Fatal(err)
		}
	}
	return buf
}

func main() {
	s1 := `[{"id":1,"user_id":1,"account_id":1,"name":"[Gmail]","attr":1,"next_uid":1,"uid_validity":1,"last_fetched_at":{"Time":"2020-07-20T17:02:59+09:00","Valid":true},"created_at":"2020-06-05T18:40:26+09:00","updated_at":"2020-07-20T17:02:59+09:00"}]
`
	s2 := bytes.NewBuffer(useFileRead("sample/test.json")).String()
	fmt.Printf("%v: %T\n", s1, s1)
	fmt.Printf("%v: %T\n", s2, s2)
	if diff := cmp.Diff(s1, s2); diff != "" {
		fmt.Printf("(-want +got):\n:%s", diff)
	}
}
