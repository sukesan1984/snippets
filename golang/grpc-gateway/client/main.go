package client

import (
	"context"
	"fmt"
	"log"
	"time"

	pb "github.com/sukesan1984/snippets/golang/grpc-gateway/proto/golang"

	"google.golang.org/grpc"
)

func Echo(conn *grpc.ClientConn, name string) {
	client := pb.NewSayHelloClient(conn)
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()

	resp, err := client.Echo(ctx, &pb.HelloRequest{UserName: name})

	if err != nil {
		log.Fatalln(err)
	}
	log.Printf("message: %s\n", resp.Message)
}

func Call(port string) {
	addr := fmt.Sprintf("localhost:" + port)
	conn, err := grpc.Dial(addr, grpc.WithInsecure())
	if err != nil {
		log.Fatalln(err)
	}
	Echo(conn, "sakas")
	defer conn.Close()
}
