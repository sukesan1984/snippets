package main

import (
	"context"
	"fmt"
	"log"
	"net"
	"net/url"

	pb "github.com/sukesan1984/snippets/golang/envoy-grpc-json/pb"
	httpbodypb "google.golang.org/genproto/googleapis/api/httpbody"
	"google.golang.org/grpc"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/metadata"
	"google.golang.org/grpc/reflection"
	"google.golang.org/grpc/status"
	emptypb "google.golang.org/protobuf/types/known/emptypb"
	"google.golang.org/protobuf/types/known/timestamppb"
	"google.golang.org/protobuf/types/known/wrapperspb"
)

const (
	port = ":50051"
)

type server struct {
	pb.UnimplementedGreeterServer
}

func (s *server) GetTest(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	point := in.GetPoint()
	if point != nil {
		fmt.Println("point is not nil")
		fmt.Printf("point is not nil: %d\n", point.GetValue())
	} else {
		fmt.Println("point is nil")
	}
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

func (s *server) TestPathParameter(ctx context.Context, in *pb.PathParameterRequest) (*pb.PathParameterResponse, error) {
	return &pb.PathParameterResponse{
		UserId: in.GetUserId(),
		Limit:  in.GetLimit(),
	}, nil
}

func (s *server) NotFoundTest(ctx context.Context, _ *emptypb.Empty) (*emptypb.Empty, error) {
	return nil, status.Error(codes.NotFound, "Not Found")
}

func (s *server) InternalTest(ctx context.Context, _ *emptypb.Empty) (*emptypb.Empty, error) {
	return nil, status.Error(codes.Internal, "Internal")
}

func (s *server) TimeTest(ctx context.Context, _ *emptypb.Empty) (*pb.TimeResponse, error) {
	return &pb.TimeResponse{
		Date: timestamppb.Now(),
	}, nil
}

func (s *server) HandleUndefinedParameter(ctx context.Context, req *pb.HandleUndefinedParameterRequest) (*pb.HandleUndefinedParameterResponse, error) {
	md, ok := metadata.FromIncomingContext(ctx)
	if !ok {
		return nil, status.Error(codes.Internal, "metadata not found")
	}
	fmt.Println(md)
	originalPath := md.Get("x-envoy-original-path")
	//urlStrings := md.Get(":authority")
	//if len(urlStrings) == 0 {
	//	return nil, status.Error(codes.Internal, "url not found")
	//}
	//fmt.Println(urlStrings)
	if len(originalPath) == 0 {
		return nil, status.Error(codes.Internal, "url not found")
	}
	fmt.Println(originalPath)

	urlString := originalPath[0]
	parsedUrl, err := url.Parse(urlString)
	if err != nil {
		return nil, status.Error(codes.Internal, "url parse error")
	}
	queryParams := parsedUrl.Query()
	fmt.Println(queryParams)

	// query parameterにunhandled_parameterというキーがあれば取り出す。なければ、not foundというstringを入れる
	unhandledParameter := queryParams.Get("unhandled_parameter")

	return &pb.HandleUndefinedParameterResponse{
		Id:                 req.GetId(),
		Name:               req.GetName(),
		UnhandledParameter: unhandledParameter,
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
