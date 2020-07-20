package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
)

type helloJSON struct {
	UserName string `json:"user_name"`
	Content  string `json:"content"`
}

func main() {
	http.HandleFunc("/hello", helloHandler)
	log.Fatal(http.ListenAndServe(":8080", nil))
}

func helloHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		w.WriteHeader(http.StatusOK)
		name := r.URL.Query().Get("name")
		fmt.Fprintf(w, "GET hello %s!\n", name)
	case http.MethodPost:
		body := r.Body
		defer body.Close()

		buf := new(bytes.Buffer)
		io.Copy(buf, body)

		var hello helloJSON
		json.Unmarshal(buf.Bytes(), &hello)

		w.WriteHeader(http.StatusCreated)
		fmt.Fprintf(w, "POST hello %v!\n", hello)
	default:
		w.WriteHeader(http.StatusMethodNotAllowed)
		fmt.Fprint(w, "Method not allowed\n")
	}
}
