protoc -I/usr/local/include -I. \
	--go_out=${GOPATH}/src \
	--go-grpc_out=${GOPATH}/src \
	-I/usr/local/opt/protobuf/include \
    -I$GOPATH/src/github.com/grpc-ecosystem/grpc-gateway/third_party/googleapis \
	-I$GOPATH/src \
	--grpc-gateway_out ${GOPATH}/src \
	--grpc-gateway_opt logtostderr=true \
	proto/service.proto
	#--grpc-gateway_opt paths=${GOPATH}/src \
