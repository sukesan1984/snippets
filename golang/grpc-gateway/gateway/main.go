package gateway

import (
	"context"
	"flag"
	"fmt"
	"log"
	"net/http"

	"github.com/golang/glog"
	"github.com/grpc-ecosystem/grpc-gateway/runtime"
	gw "github.com/sukesan1984/snippets/grpc-gateway/proto/golang"
	"google.golang.org/grpc"
)

func run(serverPort string, gwPort string) error {
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)
	defer cancel()

	mux := runtime.NewServeMux()
	opts := []grpc.DialOption{grpc.WithInsecure()}
	endpoint := fmt.Sprintf(":" + serverPort)
	err := gw.RegisterSayHelloHandlerFromEndpoint(ctx, mux, endpoint, opts)
	if err != nil {
		return err
	}
	log.Printf("gateway prot:" + gwPort)
	log.Printf("server listen: " + serverPort)
	return http.ListenAndServe(":"+gwPort, mux)
}

func Start(serverPort string, gwPort string) {
	flag.Parse()
	defer glog.Flush()
	if err := run(serverPort, gwPort); err != nil {
		glog.Fatal(err)
	}
}
