# 🚀 WebServer

![License](https://img.shields.io/badge/license-MIT-blue.svg)  
![C++](https://img.shields.io/badge/C++-blue)  
![Performance](https://img.shields.io/badge/Performance-High-success)  
![Latency](https://img.shields.io/badge/Latency-Low-brightgreen)  

**Nginx++** is a high-performance, low-latency HTTP server written in C++. Designed to handle a wide range of HTTP requests efficiently, it supports advanced features like **CGI scripting**, **file uploads**, and **custom configurations**. Built with a focus on speed and reliability. It also includes a **default index page** with a CGI script that allows users to test all supported HTTP requests directly from their browser.

---

## ✨ Features

- **High Performance**: Optimized for speed and low latency, capable of handling thousands of concurrent connections.
- **HTTP/1.1 Protocol Support**: Fully supports `GET`, `POST`, `PUT`, and `DELETE` requests.
- **CGI Support**: Execute dynamic content generation using CGI scripts (e.g., Python, PHP, Perl).
- **File Uploads**: Easily upload files with configurable storage locations.
- **Auto Indexing**: Automatically generates directory listings for directories without an `index` file.
- **Custom Configuration**: Flexible configuration via `servIO.conf` to tailor the server to your needs.
- **Dockerized**: Easy deployment using Docker for seamless integration into any environment.

---

## 🚀 Why Choose WebServer?

### ⚡ **High Performance**
WebServer is built with performance in mind. It uses efficient I/O multiplexing and a lightweight architecture to ensure minimal latency and maximum throughput. Whether you're serving static files or executing CGI scripts, WebServer delivers blazing-fast responses.

### 🕒 **Low Latency**
Thanks to its non-blocking design and optimized request handling, WebServer ensures low-latency responses even under heavy load. This makes it ideal for real-time applications and high-traffic websites.

### 🛠️ **Ease of Use**
With a simple configuration file (`servIO.conf`) and a default index page that includes a CGI script, WebServer is incredibly easy to set up and use. You can test all supported HTTP requests directly from your browser without needing external tools.

### 🐳 **Docker Support**
WebServer is fully Dockerized, making it easy to deploy in any environment. Whether you're running it locally or in the cloud, Docker ensures consistent and hassle-free deployment.

---

## 📂 Directory Structure

```
nginx++/
├── Dockerfile
├── LICENSE
├── Makefile
├── main.cpp
├── .dockerignore
├── Configuration/
│   ├── HTTP.cpp
│   ├── HTTP.hpp
│   ├── LocationConf.cpp
│   ├── LocationConf.hpp
│   ├── MainConf.cpp
│   ├── MainConf.hpp
│   ├── ServerConf.cpp
│   ├── ServerConf.hpp
│   └── servIO.conf
├── Core/
│   ├── Client.cpp
│   ├── Client.hpp
│   ├── CoreServer.cpp
│   ├── CoreServer.hpp
│   ├── Selector.hpp
│   ├── Server.cpp
│   └── Server.hpp
├── Http/
│   ├── CGI.cpp
│   ├── DefaultPages.cpp
│   ├── DefaultPages.hpp
│   ├── DeleteRequest.cpp
│   ├── DeleteRequest.hpp
│   ├── GetRequest.cpp
│   ├── GetRequest.hpp
│   ├── IRequest.hpp
│   ├── MethodsUtils.cpp
│   ├── PostRequest.cpp
│   ├── PostRequest.hpp
│   ├── ProcessRequest.cpp
│   ├── ProcessRequest.hpp
│   ├── PutRequest.cpp
│   ├── PutRequest.hpp
│   ├── Response.cpp
│   ├── Response.hpp
│   └── ResponseUtils.cpp
├── Parser/
│   ├── Lexer.cpp
│   ├── Lexer.hpp
│   ├── Parser.cpp
│   ├── Parser.hpp
│   ├── Token.cpp
│   └── Token.hpp
├── includes/
│   └── Constants.hpp
├── utils/
│   ├── utils.cpp
│   └── utils.hpp
└── www/
    ├── image/
    ├── media/
    └── other/
        ├── main.cpp
        └── test.txt
```

---

## 🛠️ Getting Started

### Prerequisites

- **C++ Compiler** (GCC or Clang)
- **Make**
- **Docker** (optional, for containerized deployment)

### 🚀 Running the Server Without Docker

1. **Clone the repository**:
   ```bash
   git clone https://github.com/abizyane/WebServer.git
   cd WebServer
   ```

2. **Build the Server**:
   Use the `Makefile` to compile the server:
   ```bash
   make
   ```

3. **Run the Server**:
   Start the server using the compiled binary:
   ```bash
   ./nginx++
   ```

4. **Access the Server**:
   Open your browser or use `curl` to access the server at `http://localhost:8080`.

---

### 🐳 Running the Server With Docker

1. **Build and Run the Docker Container**:
   Use the `Makefile` to build and start the server:
   ```bash
   make up
   ```
   This will:
   - Build the Docker image.
   - Start the container and expose ports `8080`, `5500`, and `3333`.

2. **Stop the Server**:
   To stop the server, run:
   ```bash
   make down
   ```

3. **Restart the Server**:
   To restart the server, run:
   ```bash
   make dc_re
   ```

---

## 🧪 Testing the Server

### Default Index Page with CGI Testing Interface
The server includes a **default index page** that features a CGI-powered interface. This interface allows you to test all supported HTTP requests (`GET`, `POST`, `PUT`, `DELETE`) directly from your browser. Simply navigate to `http://localhost:8080/` and use the interactive form to send requests and view responses.

### Example Requests

1. **GET Request**:
   Fetch the default page:
   ```bash
   curl http://localhost:8080/
   ```

2. **Auto Indexing**:
   If the directory has no `index` file, the server will generate an auto-indexed page. For example:
   ```bash
   curl http://localhost:8080/www/
   ```

3. **CGI Script**:
   Execute a CGI script (e.g., `app.py`):
   ```bash
   curl http://localhost:8080/www/scripts/app.py
   ```

---

## ⚙️ Configuration

The server configuration is defined in `Configuration/servIO.conf`. You can modify this file to change server settings such as ports, root directories, and allowed methods.

Example configuration:
```nginx
http {
    root /Webserv/www/;
    allow GET POST DELETE PUT;
    upload_store /Upload;
    server {
        listen 5500;
        listen 8080;
        server_name localhost;
        location / {
            error_page 404 404.html;
            cgi 0.0.0.0:90;
            autoindex on;
            index indexxx.html app.py;
            client_body_max_size 300;
            cgi .py .js .php .pl;
        }
        location /www/scripts {
            root /Webserv/www/scripts;
            autoindex on;
            cgi .py;
        }
        location /blog {
            deny DELETE;
        }
        location /container_rootdir {
            deny POST;
            deny DELETE;
            deny PUT;
            root /;
            autoindex on;
        }
    }
    server {
        listen 3333;
        location / {
            return 301 http://localhost:8080;
        }
    }
}
```

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👏 Acknowledgments

- **Zakaria El Bouzkri** 🧑‍💻
- **Achraf Bizyane** 🧑‍💻
- **Noureddine Akebli** 🧑‍💻


---

## 🌟 Inspired By

- The simplicity and performance of **Nginx**.
- The power of **C++**.

---
