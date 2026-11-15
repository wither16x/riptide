#include <std.h>
#include <cerrno>
#include <cstring>

import riptide.net.port;
import riptide.net.socket;

auto main() -> int {
    try {
        riptide::net::socket::Socket socket;

        socket.connect();
        std::println("OK: connected to the server");

        std::size_t len = socket.read(1024).size();
        std::println("INFO: read {} bytes from socket", len);
    } catch (const std::exception &e) {
        std::println("ERROR: {}: {}", e.what(), std::strerror(errno));
    }

    return 0;
}