package server

import (
	"context"
	"fmt"
	"grpc-go-auth/pb"
)

type helloServer struct {
}

func NewHelloServer() *helloServer {
	return &helloServer{}
}

func (s *helloServer) Hello(
	ctx context.Context,
	req *pb.HelloRequest,
) (*pb.HelloResponse, error) {
	return &pb.HelloResponse{Answer: fmt.Sprintf("Hello %s", req.Message)}, nil
}

func (s *helloServer) TellMeSecret(
	ctx context.Context,
	req *pb.TellMeSecretRequest,
) (*pb.TellMeSecretResponse, error) {
	return &pb.TellMeSecretResponse{Answer: fmt.Sprintf("Secret %s", req.Message)}, nil
}
