protoc -I/usr/local/include -I. \
	--go_out=${GOPATH}/src \
	--go-grpc_out=${GOPATH}/src \
    -I$GOPATH/src/github.com/grpc-ecosystem/grpc-gateway/third_party/googleapis \
	-I/usr/local/opt/protobuf/include \
	-I$GOPATH/src \
	--include_imports \
	--descriptor_set_out=${GOPATH}/src/github.com/sukesan1984/snippets/golang/envoy-grpc-json/pb/helloworld.pb \
	pb/helloworld.proto
	#--include_source_info \
	#--grpc-gateway_opt paths=${GOPATH}/src \
