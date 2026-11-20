module;
#include <std.h>

export module riptide.net.packet;

import riptide.net.types;
import riptide.net.port;

namespace riptide::net::packet {

/**
 * @brief A packet without compression.
 */
export struct Packet {
    types::VarInt length;
    types::VarInt id;
    types::VarInt protocol_version;
    types::VarInt strlength;
    types::ByteArray str;
    types::UnsignedShort port;
    types::VarInt next_state;
};

auto write(std::vector<std::uint8_t> &out, port::Port v) -> void {
    out.push_back(v >> 8);
    out.push_back(v & 0xff);
}

auto write(std::vector<std::uint8_t> &out, const types::ByteArray &bytes) -> void {
    write(out, bytes.size());
    out.insert(out.end(), bytes.begin(), bytes.end());
}

export template<typename T>
auto serialize(const T &obj) -> std::vector<std::uint8_t> {
    std::vector<std::uint8_t> out;
   template for (constexpr auto member : std::define_static_array(
    std::meta::nonstatic_data_members_of(^^T, std::meta::access_context::current())))
        write(out, obj.[:member:]);
    return out;
}

} // namespace riptide::net::packet