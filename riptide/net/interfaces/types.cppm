module;
#include <std.h>

export module riptide.net.types;

import riptide.utils.error;

namespace riptide::net::types {

// Data types according to
// https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_types_(v47)

using Boolean = std::uint8_t;
constexpr Boolean FALSE = 0x00;
constexpr Boolean TRUE = 0x01;

using Byte = std::int8_t;
using UnsignedByte = std::uint8_t;
using Short = std::int16_t;
using UnsignedShort = std::uint16_t;
using Int = std::int32_t;
using Long = std::int64_t;
using Float = float;
using Double = double;

// Must not be used as a std::int32_t!
// This type must be used with the function read_varint().
using VarInt = std::int32_t;

constexpr VarInt read_varint(std::span<std::uint8_t> buf)
{
    std::uint8_t bitoff = 0;
    std::uint8_t currbyte = 0;
    std::uint32_t uresult = 0;
    std::uint8_t nreadtmp = 0;

    do {
        if (bitoff == 35)
            throw utils::error::RiptideException("VarInt is too big");

        currbyte = buf[nreadtmp++];
        uresult |= static_cast<std::uint32_t>((currbyte & 0x7f)) << bitoff;
        bitoff += 7;
    } while (currbyte & 0x80);

    return static_cast<VarInt>(uresult);
}

// Must not be used as a std::int64_t!
// This type must be used with the function read_varlong().
using VarLong= std::int64_t;

constexpr VarLong read_varlong(std::span<std::uint8_t> buf)
{
    std::uint8_t bitoff = 0;
    std::uint8_t currbyte = 0;
    std::uint32_t uresult = 0;
    std::uint8_t nreadtmp = 0;

    do {
        if (bitoff == 70)
            throw utils::error::RiptideException("VarLong is too big");

        currbyte = buf[nreadtmp++];
        uresult |= static_cast<std::uint32_t>((currbyte & 0x7f)) << bitoff;
        bitoff += 7;
    } while (currbyte & 0x80);

    return static_cast<VarLong>(uresult);
}

} // namespace riptide::net::types