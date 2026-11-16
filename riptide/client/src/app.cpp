module riptide.client.app;

import riptide.net.socket;
import riptide.utils.logging;

namespace riptide::client::app {

auto App::run() -> void {
    net::socket::Socket socket;

    socket.connect();
    utils::logging::ok("connected to the server");

    std::size_t len = socket.read(1024).size();
    utils::logging::info("read {} bytes from socket", len);

    utils::logging::info("disconnected from server");
}

} // namespace riptide::client::app