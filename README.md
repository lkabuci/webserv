# webserv

A fully compliant **HTTP/1.1 web server** written in C++98, built from scratch using the **Reactor design pattern** with non-blocking I/O multiplexing. Supports multiple virtual servers, CGI execution, static file serving, and a custom Nginx-style configuration format.

---

## Table of Contents

- [Features](#features)
- [Architecture](#architecture)
- [Requirements](#requirements)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Expected Output](#expected-output)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [Resources](#resources)
- [License](#license)

---

## Features

- **HTTP/1.1** compliant — GET, POST, DELETE methods
- **Non-blocking I/O** via `select`/`poll`-based Reactor pattern
- **Multiple virtual servers** on different ports/addresses
- **CGI support** — Python (`.py`) and Ruby (`.rb`) scripts
- **Static file serving** with directory autoindex
- **Custom error pages** (404, 500, etc.)
- **HTTP redirects** (301, 302, etc.)
- **Configurable upload size** (`client_max_body_size`)
- **Nginx-style configuration** parser with full lexing/parsing pipeline
- **Graceful shutdown** via signal handling (SIGINT, SIGTERM)
- **Docker** support for isolated unit testing with GoogleTest

---

## Architecture

The server is built around the **Reactor** concurrency pattern:

```
┌──────────────────────────────────────────────────┐
│                     Reactor                       │
│                                                   │
│  ┌─────────────────┐    ┌──────────────────────┐  │
│  │  Demultiplexer  │───▶│     Dispatcher       │  │
│  │  (select/poll)  │    │ (event routing)      │  │
│  └─────────────────┘    └──────────┬───────────┘  │
│                                    │               │
│              ┌─────────────────────┤               │
│              ▼                     ▼               │
│  ┌────────────────────┐  ┌──────────────────────┐  │
│  │ ServerEventHandler │  │ ClientEventHandler   │  │
│  │ (accept new conn)  │  │ (read/write/CGI)     │  │
│  └────────────────────┘  └──────────────────────┘  │
└──────────────────────────────────────────────────┘
```

HTTP request handling follows the **Strategy pattern** — each HTTP method (GET, POST, DELETE) is encapsulated in its own strategy class, selected at dispatch time.

---

## Requirements

| Dependency | Version       |
|------------|---------------|
| C++ compiler | C++98 compatible (`g++`, `clang++`) |
| Make       | Any modern version |
| Python 3   | For `.py` CGI scripts (optional) |
| Ruby       | For `.rb` CGI scripts (optional) |
| Docker + Docker Compose | For running unit tests (optional) |

---

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/kaboussi/webserv.git
cd webserv
```

### 2. Build the server

```bash
make
```

This compiles all sources into the `build/` directory and produces the `webserv` binary.

### Other build targets

| Command      | Description                          |
|--------------|--------------------------------------|
| `make`       | Build the `webserv` binary           |
| `make clean` | Remove object files and build artifacts |
| `make fclean`| Remove everything including the binary |
| `make re`    | Full rebuild (`fclean` + `all`)      |

---

## Configuration

The server reads an Nginx-style configuration file. A default configuration is provided at `config/webserv.conf`.

### Configuration syntax

```nginx
server {
    listen 127.0.0.1:8000;        # Bind address and port
    server_name main;              # Virtual server name
    root ./root;                   # Document root
    client_max_body_size 10m;      # Max upload body size (k/m/g suffix)

    index index.html;              # Default index file

    error_page 404 /errors/404.html;  # Custom error pages
    error_page 500 /errors/500.html;

    location /cgi {
        root ./root/cgi-bin;
        autoindex on;              # Enable directory listing
        allow_methods GET POST;    # Restrict allowed HTTP methods
    }

    location /static {
        root ./root/static;
        allow_methods GET;
    }

    location /rick {
        return 301 https://example.com;  # HTTP redirect
    }

    location ~ \.py$ {             # Regex location — Python CGI
        root ./root/cgi-bin/;
        allow_methods GET POST;
    }

    location ~ \.rb$ {             # Regex location — Ruby CGI
        root ./root/cgi-bin;
        allow_methods GET POST;
    }
}
```

### Multiple virtual servers

You can define multiple `server { }` blocks in the same config file. Each server can listen on a different port or address:

```nginx
server {
    listen 127.0.0.1:8000;
    # ...
}

server {
    listen :8080;
    # ...
}
```

### Directives reference

| Directive              | Scope           | Description                                      |
|------------------------|-----------------|--------------------------------------------------|
| `listen`               | server          | Address and port to bind (`[addr:]port`)         |
| `server_name`          | server          | Virtual server hostname                          |
| `root`                 | server/location | Document root directory                          |
| `index`                | server/location | Default file for directory requests              |
| `client_max_body_size` | server          | Max allowed request body size                    |
| `error_page`           | server          | Map HTTP error codes to custom pages             |
| `location`             | server          | Define a URI prefix or regex block               |
| `allow_methods`        | location        | Whitelist of allowed HTTP methods                |
| `autoindex`            | location        | Toggle directory listing (`on`/`off`)            |
| `return`               | location        | Issue an HTTP redirect                           |

---

## Usage

### Start the server

```bash
./webserv config/webserv.conf
```

The server prints its PID on startup and begins listening on all configured addresses:

```
pid: 12345
```

### Send requests with curl

**GET a static page:**
```bash
curl http://127.0.0.1:8000/
```

**POST data:**
```bash
curl -X POST http://127.0.0.1:8000/upload \
     -H "Content-Type: text/plain" \
     --data "Hello, webserv!"
```

**DELETE a resource:**
```bash
curl -X DELETE http://127.0.0.1:8000/files/old.txt
```

**CGI script execution:**
```bash
curl "http://127.0.0.1:8000/cgi/hello.py?name=World"
```

### Stop the server

Send `SIGINT` or `SIGTERM` to stop the server gracefully:

```bash
kill -SIGINT <pid>
# or simply press Ctrl+C in the terminal
```

---

## Expected Output

### Successful GET request

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 512

<!DOCTYPE html>
<html>
  ...
</html>
```

### 404 Not Found

When a requested file does not exist, the server responds with the configured error page:

```
HTTP/1.1 404 Not Found
Content-Type: text/html
Content-Length: 218
```

### 301 Redirect

When hitting a redirect location:

```
HTTP/1.1 301 Moved Permanently
Location: https://example.com
Content-Length: 0
```

### Autoindex (directory listing)

When `autoindex on` is set and no index file exists, the server generates an HTML directory listing:

```
HTTP/1.1 200 OK
Content-Type: text/html

<html>
<head><title>Index of /cgi</title></head>
<body>
  <h1>Index of /cgi</h1>
  <ul>
    <li><a href="hello.py">hello.py</a></li>
    ...
  </ul>
</body>
</html>
```

### CGI execution

Python/Ruby scripts under a CGI location are executed as child processes. The script's stdout becomes the HTTP response body:

```
HTTP/1.1 200 OK
Content-Type: text/plain

Hello, World!
```

### Method not allowed

Requests using a method not listed in `allow_methods`:

```
HTTP/1.1 405 Method Not Allowed
Content-Length: 0
```

---

## Testing

### Unit tests (Docker)

Unit tests use **GoogleTest** and run inside Docker for a reproducible environment:

```bash
make unittest
```

This command builds the Docker image (if needed), runs the test suite, and cleans up.

### Manual testing with curl

```bash
# Test GET
curl -v http://127.0.0.1:8000/

# Test POST with a file upload
curl -v -X POST http://127.0.0.1:8000/upload \
     -F "file=@/path/to/file.txt"

# Test DELETE
curl -v -X DELETE http://127.0.0.1:8000/files/target.txt

# Test redirect
curl -v http://127.0.0.1:8000/rick

# Test autoindex
curl -v http://127.0.0.1:8000/cgi/
```

---

## Project Structure

```
webserv/
├── config/
│   └── webserv.conf          # Default server configuration
├── docs/                     # Design notes and references
│   └── dev/
│       └── reactor.md        # Reactor/Dispatcher architecture notes
├── include/
│   └── webserv.hpp           # Top-level header aggregator
├── root/                     # Default web root (served content)
│   ├── index.html
│   ├── cgi-bin/              # CGI script directory
│   ├── errors/               # Custom error pages (404, 500)
│   └── msmen/                # Static sub-site example
├── src/
│   ├── main.cpp              # Entry point
│   ├── Webserver.cpp/hpp     # Server bootstrap
│   ├── config/               # Configuration lexer + parser
│   │   ├── Lexer.*           # Tokenizer
│   │   ├── Parser.*          # Grammar/syntax parser
│   │   ├── ServerConfig.*    # Per-server config model
│   │   ├── LocationConfig.*  # Per-location config model
│   │   └── ...
│   ├── http/                 # HTTP protocol layer
│   │   ├── Request.*         # Request parsing
│   │   ├── Header.*          # Header handling
│   │   ├── HTTP.*            # Response builder
│   │   └── StatusLine.*      # Status line parsing
│   ├── methods/              # HTTP method strategies
│   │   ├── IRequestStrategy.hpp
│   │   ├── GETRequestStrategy.*
│   │   ├── POSTRequestStrategy.*
│   │   └── DELETERequestStrategy.*
│   ├── reactor/              # Reactor concurrency pattern
│   │   ├── Reactor.*         # Core event loop
│   │   ├── Demultiplexer.*   # I/O event detection
│   │   ├── Dispatcher.*      # Event routing
│   │   ├── ServerEventHandler.*  # Accept new connections
│   │   └── ClientEventHandler.*  # Handle client I/O
│   ├── stream/               # Socket/server stream abstractions
│   ├── helpers/              # Shared utilities
│   └── utils/                # Signal handling, misc tools
├── test/                     # Unit tests (GoogleTest)
├── Examples/
│   └── request.http          # Sample raw HTTP requests
├── Dockerfile                # Docker image for testing
├── compose.yml               # Docker Compose configuration
├── Makefile                  # Primary build system
├── Makefile-test             # Test build system
└── LICENSE
```

---

## Resources

- [RFC 2616 — HTTP/1.1](https://tools.ietf.org/html/rfc2616)
- [The Linux Programming Interface](https://www.amazon.com/Linux-Programming-Interface-System-Handbook/dp/1593272202) — Chapters 56–61 (Sockets)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/)
- [Reactor Design Pattern — Schmidt](https://www.dre.vanderbilt.edu/~schmidt/PDF/reactor-siemens.pdf)
- [Crafting Interpreters](https://craftinginterpreters.com/contents.html) — Lexer/parser design

---

## License

This project is licensed under the [MIT License](LICENSE).
