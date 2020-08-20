package main

import (
	"grpc-go-auth/pb"
	"grpc-go-auth/server"
	"log"
	"net"

	grpc_middleware "github.com/grpc-ecosystem/go-grpc-middleware"
	grpc_auth "github.com/grpc-ecosystem/go-grpc-middleware/auth"
	"google.golang.org/grpc"
)

func main() {
	log.Println("start")
	listener, err := net.Listen("tcp", "127.0.0.1:8088")
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	gRPCServer := grpc.NewServer(
		grpc.UnaryInterceptor(grpc_middleware.ChainUnaryServer(
			grpc_auth.UnaryServerInterceptor(server.AuthFunc),
			server.AuthorizationUnaryServerInterceptor(),
		)),
	)

	pb.RegisterHelloServiceServer(gRPCServer, server.NewHelloServer())

	err = gRPCServer.Serve(listener)
	if err != nil {
		log.Fatalf("could not start gRPC server: %v", err)
	}
}
