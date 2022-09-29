package main

import (
	"context"
	"log"
	"net"

	pb "github.com/sukesan1984/snippets/golang/envoy-grpc-json/pb"
	httpbodypb "google.golang.org/genproto/googleapis/api/httpbody"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
	"google.golang.org/protobuf/types/known/wrapperspb"
)

const (
	port = ":50051"
)

type server struct {
	pb.UnimplementedGreeterServer
}

func (s *server) GetTest(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	return &pb.HelloResponse{
		Message: "Hello World",
		Orders: []*pb.Order{
			{
				Id: "order1",
				Items: []*pb.Item{
					{
						Id:    "hoge",
						Name:  "日本製 ガーゼハンドタオル スピードライ speedry (宅配) ひよこクラブ掲載 ガーゼタオル 表面ガーゼ地 裏面パイル地 ハンカチ ガーゼハンカチ タオルハンカチ 速乾軽量 薄手 赤ちゃん ベビー 無地(0103-0006-010111)",
						Price: wrapperspb.Double(1),
					},
					{
						Id: "fuga",
					},
				},
			},
			{
				Id: "order2",
				Items: []*pb.Item{
					{Id: "hoge2"},
					{Id: "fuga2"},
				},
			},
		},
	}, nil
}

func (s *server) PostTest(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	return &pb.HelloResponse{
		Message: "Hello " + in.Name,
		Orders: []*pb.Order{
			{
				Id: "order1",
				Items: []*pb.Item{
					{Id: "hoge"},
					{Id: "fuga"},
				},
			},
			{
				Id: "order2",
				Items: []*pb.Item{
					{Id: "hoge2"},
					{Id: "fuga2"},
				},
			},
		},
	}, nil
}

func (s *server) GetInt(ctx context.Context, in *pb.IntRequest) (*httpbodypb.HttpBody, error) {
	//func (s *server) GetInt(ctx context.Context, in *pb.IntRequest) (*wrapperspb.Int64Value, error) {
	//func (s *server) GetInt(ctx context.Context, _ *pb.IntRequest) (*pb.IntResponse, error) {
	return &httpbodypb.HttpBody{
		//return &pb.IntResponse{
		ContentType: "text/plain",
		Data:        []byte{0x32},
	}, nil
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
		log.Fatalf("failed to serve: %v", err)
	}
}
