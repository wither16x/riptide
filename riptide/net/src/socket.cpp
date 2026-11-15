module;
#include <unistd.h>
#include <sys/socket.h>
#include <std.h>
#include <netdb.h>

module riptide.net.socket;

import riptide.net.port;
import riptide.utils.error;

namespace riptide::net::socket {

namespace detail {

auto create_socket() -> int {
    int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        throw utils::error::RiptideException("failed to create socket");
    return sockfd;
}

auto destroy_socket(int sockfd) -> void {
    if (::close(sockfd) == -1)
        throw std::runtime_error("failed to close socket");
}

auto create_socket_address() -> sockaddr_in {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(riptide::net::port::DEFAULT_SEVER_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    return addr;
}

} // namespace detail

Socket::Socket()
    : fd_(detail::create_socket()),
      addr_(detail::create_socket_address())
{}

Socket::~Socket()
{
    detail::destroy_socket(fd_);
}

auto Socket::connect() -> void {
    if (::connect(fd_, reinterpret_cast<sockaddr *>(&addr_), sizeof(addr_)) != 0)
        throw std::runtime_error("failed to connect to server");
}

auto Socket::read(std::size_t count) -> std::vector<std::uint8_t> {
    std::vector<std::uint8_t> data(count);
    ssize_t bytes_read = ::read(fd_, data.data(), count);
    if (bytes_read == -1)
        throw std::runtime_error("failed to read from socket");

    data.resize(static_cast<std::size_t>(bytes_read));
    return data;
}

} // namespace riptide::net::socket