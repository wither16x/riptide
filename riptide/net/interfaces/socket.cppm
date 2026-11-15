module;
#include <netdb.h>
#include <std.h>

export module riptide.net.socket;

namespace riptide::net::socket {

/**
 * @brief RAII wrapper around an UNIX socket.
 *
 * Not copyable nor movable.
 */
export class Socket {
public:
    Socket();
    Socket(const Socket &) = delete("sockets are not copyable");
    Socket(Socket &&other) = delete("sockets are not movable");

    ~Socket();

    auto connect() -> void;
    auto read(std::size_t count) -> std::vector<std::uint8_t>;

    Socket &operator =(const Socket &) = delete("sockets are not copyable");
    Socket &operator =(Socket &&other) = delete("sockets are not movable");

private:
    int fd_;
    sockaddr_in addr_;
};

} // namespace riptide::net::socket