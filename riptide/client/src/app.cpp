module riptide.client.app;

import riptide.net.socket;

namespace riptide::client::app {

auto App::run() -> void {
    net::socket::Socket socket;

    socket.connect();
    std::println("OK: connected to the server");

    std::size_t len = socket.read(1024).size();
    std::println("INFO: read {} bytes from socket", len);
}

} // namespace riptide::client::app