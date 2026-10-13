/*
  Rochdale Village NORC - tiny C++ HTTP server
  ------------------------------------------------
  Optional backend for the website.

  Build on Linux/macOS:
      g++ -std=c++17 -O2 server.cpp -o norc_server
      ./norc_server

  Build on Windows with MinGW:
      g++ -std=c++17 -O2 server.cpp -lws2_32 -o norc_server.exe
      norc_server.exe

  Then open:
      http://localhost:8080

  Client submissions are appended to:
      client_submissions.txt

  This is a simple educational/local server. For a public production
  deployment, use HTTPS, authentication, input validation, a database,
  CSRF protection, logging, and a production web server.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <filesystem>

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #pragma comment(lib, "Ws2_32.lib")
  using socket_t = SOCKET;
  #define CLOSESOCKET closesocket
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <unistd.h>
  using socket_t = int;
  #define CLOSESOCKET close
#endif

const int PORT = 8080;

std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return "";
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::string contentType(const std::string& path) {
    if (path.ends_with(".html")) return "text/html; charset=UTF-8";
    if (path.ends_with(".css")) return "text/css; charset=UTF-8";
    if (path.ends_with(".js")) return "application/javascript; charset=UTF-8";
    return "text/plain; charset=UTF-8";
}

std::string jsonValue(const std::string& body, const std::string& key) {
    std::string target = "\"" + key + "\"";
    size_t p = body.find(target);
    if (p == std::string::npos) return "";
    p = body.find(':', p);
    if (p == std::string::npos) return "";
    p = body.find('"', p);
    if (p == std::string::npos) return "";
    size_t end = p + 1;
    while (end < body.size()) {
        if (body[end] == '"' && body[end - 1] != '\\') break;
        end++;
    }
    return body.substr(p + 1, end - p - 1);
}

void sendResponse(socket_t client, const std::string& status,
                  const std::string& type, const std::string& body) {
    std::ostringstream response;
    response << "HTTP/1.1 " << status << "\r\n"
             << "Content-Type: " << type << "\r\n"
             << "Content-Length: " << body.size() << "\r\n"
             << "Access-Control-Allow-Origin: *\r\n"
             << "Connection: close\r\n\r\n"
             << body;
    std::string out = response.str();
    send(client, out.c_str(), static_cast<int>(out.size()), 0);
}

int main() {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }
#endif

    socket_t server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        std::cerr << "Could not create socket.\n";
        return 1;
    }

    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR,
#ifdef _WIN32
               reinterpret_cast<const char*>(&opt), sizeof(opt));
#else
               &opt, sizeof(opt));
#endif

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        std::cerr << "Bind failed. Is port " << PORT << " already in use?\n";
        CLOSESOCKET(server);
        return 1;
    }

    listen(server, 10);
    std::cout << "NORC website running at http://localhost:" << PORT << "\n";

    while (true) {
        socket_t client = accept(server, nullptr, nullptr);
        if (client < 0) continue;

        char buffer[16384]{};
        int received = recv(client, buffer, sizeof(buffer) - 1, 0);
        if (received <= 0) {
            CLOSESOCKET(client);
            continue;
        }

        std::string request(buffer, received);
        size_t lineEnd = request.find("\r\n");
        std::string requestLine = request.substr(0, lineEnd);

        if (requestLine.rfind("POST /api/client", 0) == 0) {
            size_t bodyStart = request.find("\r\n\r\n");
            std::string body = bodyStart == std::string::npos ? "" : request.substr(bodyStart + 4);

            std::ofstream out("client_submissions.txt", std::ios::app);
            out << "----------------------------------------\n";
            out << "Name: " << jsonValue(body, "name") << "\n";
            out << "Email: " << jsonValue(body, "email") << "\n";
            out << "Phone: " << jsonValue(body, "phone") << "\n";
            out << "Interest: " << jsonValue(body, "interest") << "\n";
            out << "Message: " << jsonValue(body, "message") << "\n";

            sendResponse(client, "200 OK", "application/json",
                         R"({"success":true})");
        } else {
            std::string path = "index.html";
            if (requestLine.rfind("GET /style.css", 0) == 0) path = "style.css";
            else if (requestLine.rfind("GET /script.js", 0) == 0) path = "script.js";
            else if (requestLine.rfind("GET / ", 0) == 0 || requestLine.rfind("GET /?", 0) == 0) path = "index.html";

            std::string data = readFile(path);
            if (data.empty()) {
                sendResponse(client, "404 Not Found", "text/plain", "404 Not Found");
            } else {
                sendResponse(client, "200 OK", contentType(path), data);
            }
        }

        CLOSESOCKET(client);
    }

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
