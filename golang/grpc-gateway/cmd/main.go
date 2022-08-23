package main

import (
	"github.com/sukesan1984/snippets/grpc-gateway/client"
	"github.com/sukesan1984/snippets/grpc-gateway/server"
)

func main() {
	serverPort := "19003"

	go func() {
		server.Start(serverPort)
	}()

	client.Call(serverPort)
}
