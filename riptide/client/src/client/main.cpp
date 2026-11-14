#include <std.h>

import client.math;

auto main() -> int {
    std::println("3 + 4 = {}", client::math::add(3, 4));
    return 0;
}