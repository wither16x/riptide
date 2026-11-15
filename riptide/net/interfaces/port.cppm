module;
#include <std.h>

export module riptide.net.port;

namespace riptide::net::port {

/**
 * @brief A server port.
 */
export using Port = std::uint16_t;

/**
 * @brief Minecraft servers listen to this port by default.
 */
export constexpr Port DEFAULT_SEVER_PORT = 25565;

} // namespace riptide::net::port