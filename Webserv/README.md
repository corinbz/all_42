# Webserv

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/language-C%2B%2B11-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

An HTTP/1.1 server written from scratch in C++11: a non-blocking,
single-threaded event loop over `poll()`, an NGINX-style configuration
file, static file serving, uploads, directory listing, redirects and CGI.

## Usage

```sh
./webserv [config_file]   # defaults to a built-in config if omitted
```

## Configuration

NGINX-inspired block syntax; see `config/default.config` for a full
example:

```
http {
    server_timeout_time    10000
    server {
        index               index.html
        server_name         localhost
        listen              8080
        root                www
        keepalive_timeout   40
        send_timeout        15
        max_body_size       10000000
        directory_listing   true
        location / {
            request_types   GET POST
        }
        location /uploads {
            request_types   GET POST DELETE
        }
        location /codam {
            request_types   GET
            redirection     https://www.codam.nl/
        }
    }
}
```

Multiple `server` blocks let one binary serve several virtual hosts on
different ports; each `location` block scopes allowed HTTP methods,
redirects, and (implicitly) CGI/upload behavior to a URL prefix.
`config/invalid1.config`, `invalid2.config`, `min_invalid.config` are
fixtures for the config-parser's error handling.

## Features

- `GET`, `POST`, `DELETE` per-location method restrictions
  (`HttpMethods`)
- Static file serving with configurable document root and index file
- Directory listing (toggle per server)
- File uploads (`www/uploads/`)
- CGI execution (`www/cgi/*.py`)
- HTTP redirects per location
- Per-server `max_body_size`, `keepalive_timeout`, `send_timeout`
- Multiple listening sockets multiplexed on one `poll()` loop — no thread
  or process is spawned per connection

## Architecture

- **`ConfigHandler`** — hand-written recursive-descent parser for the
  `http { server { location { ... } } }` block syntax, producing an
  `HttpConfig` tree of `ServerConfig`/`LocationConfig` and validating it
  (`verifyConfiguration`).
- **`Server`** — owns every listening and client socket. `createSocket` /
  `bindSocket` set up one non-blocking listener per configured `server`
  block; the main loop calls `poll()` over all of them plus every active
  client fd, `acceptClientSocket`s new connections, and dispatches
  readable/writable clients through `t_client_state`. `selectServerConfig`
  picks the right virtual host by `Host:` header + port.
- **`HttpRequest`** — incremental parser for the request line, headers and
  body (handles `Content-Length` and chunked bodies as they arrive across
  multiple `poll()` wakeups).
- **`HttpResponse`** — builds status line, headers and body for static
  files, directory listings, redirects, uploads and CGI output.

## Build

```sh
make        # builds webserv (c++ -std=c++11 -fsanitize=address -g -Wall -Wextra -Werror)
make clean
make fclean
make re
```

## Files

| Path | Role |
|------|------|
| `src/main.cpp` | Entry point, config load, `Server` startup |
| `src/Server.cpp` / `includes/Server.hpp` | Event loop, socket + connection lifecycle |
| `src/ConfigHandler.cpp` / `includes/ConfigHandler.hpp` | Config file parsing/validation |
| `src/HttpRequest.cpp` / `includes/HttpRequest.hpp` | Request parsing |
| `src/HttpResponse.cpp` / `includes/HttpResponse.hpp` | Response building |
| `src/utils.cpp` / `includes/utils.hpp` | Shared helpers and config data types |
| `config/` | Example and invalid configuration files |
| `www/` | Document root: static pages, images, CGI scripts, uploads |
