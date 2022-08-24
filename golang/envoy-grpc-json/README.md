`docker-compose run --rm server /bin/sh`
# containerの中で
- `cd src`
- `go build -o server/bin/server server/main.go`
- `exit`

# containerの外で
- docker-compose down
- docker-compose up -d 

# curl
- `curl  http://localhost:51051/hello -v`
