package main

import (
	"context"
	"net"

	pb "github.com/sukesan1984/snippets/golang/envoy-grpc-json/pb"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
)

const (
	port = ":50051"
)

type server struct{}

func (s *server) GetTest(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	return &pb.HelloReponse{Message: "Hello World"}, nil
}

func (s *server) PostTest(ctx context.Context, in *pb.HelloRequest) (*pb.HelloReponse, error) {
	return &pb.HelloReponse{Message: "Hello " + in.Name}, nil
}

func main() {
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	pb.RegisterGreeterServer(s, &server{})
	reflection.Register(s)
	if err := s.Serve(lis); err != nil {
		log.Faltaf("failed to serve: %v", err)
	}
}
