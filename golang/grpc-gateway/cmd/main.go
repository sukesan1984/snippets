package main

import (
	"github.com/sukesan1984/snippets/golang/grpc-gateway/gateway"
	"github.com/sukesan1984/snippets/golang/grpc-gateway/server"
)

func main() {
	serverPort := "19003"
	gwPort := "50000"

	go func() {
		server.Start(serverPort)
	}()

	gateway.Start(serverPort, gwPort)
	//client.Call(serverPort)
}
