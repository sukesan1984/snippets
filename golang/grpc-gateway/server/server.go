package server

import (
	"context"
	"fmt"
	"log"
	"net"

	pb "github.com/sukesan1984/snippets/golang/grpc-gateway/proto/golang"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
)

type helloService struct {
	pb.UnimplementedSayHelloServer
}

func (hs *helloService) Echo(ctx context.Context, req *pb.HelloRequest) (*pb.HelloResponse, error) {
	fmt.Println(req.String())
	return &pb.HelloResponse{
		Message: "hello, " + req.UserName,
		Orders: []*pb.Order{
			{
				Name: "order1",
				Items: []*pb.Item{
					{Id: "hoge"},
					{Id: "fuga"},
				},
			},
			{
				Name: "order2",
				Items: []*pb.Item{
					{Id: "hoge2"},
					{Id: "fuga2"},
				},
			},
		},
	}, nil
}

func Start(port string) {
	listen, err := net.Listen("tcp", ":"+port)
	if err != nil {
		log.Fatalln(err)
	}

	log.Printf("server listen: " + listen.Addr().String())
	server := grpc.NewServer()
	pb.RegisterSayHelloServer(server, &helloService{})
	reflection.Register(server)

	if err := server.Serve(listen); err != nil {
		log.Fatalln(err)
	}
}
