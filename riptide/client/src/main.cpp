#include <cerrno>
#include <cstring>

import riptide.client.app;

auto main() -> int {
    try {
        riptide::client::app::App app;
        app.run();
    } catch (const std::exception &e) {
        std::println("ERROR: {}: {}", e.what(), std::strerror(errno));
    }

    return 0;
}