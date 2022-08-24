# envoy gRPC-JSON transcoderテスト
- https://qiita.com/samskeyti/items/c4b0f3cc78389654ac9d

# containerの中
- `docker-compose run --rm server /bin/sh`
- `cd src`
- `go build -o server/bin/server server/main.go`
- `exit`

# containerの外で
- `docker-compose down`
- `docker-compose up -d`

# curl
- `curl  http://localhost:51051/hello -v`
