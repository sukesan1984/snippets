FROM golang:1.21.0-alpine as builder

RUN apk add --no-cache curl git go unzip musl-dev libc6-compat

ENV PROTOBUF_VERSION 3.11.4

RUN curl -sL https://github.com/google/protobuf/releases/download/v${PROTOBUF_VERSION}/protoc-${PROTOBUF_VERSION}-linux-x86_64.zip -o /tmp/protoc.zip && \
    unzip /tmp/protoc.zip -d /tmp && \
    cp -r /tmp/bin /tmp/include /usr/local/ && \
    rm -rf /tmp/*

COPY . /src

ENV GOPATH /go
ENV PATH $PATH:$GOPATH/bin:/usr/local/go/bin

WORKDIR /src

RUN go mod download
RUN CGO_ENABLED=0 GOOS=linux go build -o /main /src/server/main.go
RUN ls -la /main
RUN cat /main

FROM gcr.io/distroless/base-debian10

COPY --from=builder /main /
CMD ["/main"]
