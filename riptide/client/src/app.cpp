module;
#include <sys/socket.h>
#include <std.h>

module riptide.client.app;

import riptide.net.socket;
import riptide.net.packet;
import riptide.utils.logging;

namespace riptide::client::app {

auto App::run() -> void {
    net::socket::Socket socket;

    socket.connect();
    utils::logging::ok("connected to the server");

    net::packet::Packet packet = {
        .length = 16,
        .id = 0,
        .protocol_version = 47,
        .strlength = 9,
        .str = "127.0.0.1",
        .port = 25565,
        .next_state = 1
    };

    const std::uint8_t buf[] = {
        // handshake packet
        // 0xf: packet length (VARINT)
        // 0x00: packet ID (0x00 = Handshake) (VARINT)
        // 0x2f: protocol version (47) (VARINT)
        // 0x09: length of the following string
        // 0x31 - 0x31: "127.0.0.1" (host)
        // 0x63dd: port (25565)
        // 0x01: next state (status) (VARINT)
        // 0x0f, 0x00, 0x2f, 0x09,
        // 0x31, 0x32, 0x37, 0x2e, 0x30, 0x2e, 0x30, 0x2e, 0x31,
        // 0x63, 0xdd,
        // 0x01,

        // status request packet
        // 0x01: packet length (VARINT)
        // 0x00: packet ID (VARINT)
        0x01, 0x00
    };
    socket.send(serialize(packet));
    socket.send(buf);
    utils::logging::debug("sent request");

    auto response = socket.receive(65535);

    utils::logging::info("received {}", std::string_view{
        reinterpret_cast<const char *>(response.data()),
        response.size()
    });
}

} // namespace riptide::client::app