protoc -I/usr/local/include -I. \
	--go_out=${GOPATH}/src \
	--go-grpc_out=${GOPATH}/src \
    -I$GOPATH/src/github.com/grpc-ecosystem/grpc-gateway/third_party/googleapis \
	-I/usr/local/opt/protobuf/include \
	-I$GOPATH/src \
	pb/helloworld.proto
	#--grpc-gateway_opt paths=${GOPATH}/src \
