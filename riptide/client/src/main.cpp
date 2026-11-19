#include <cerrno>
#include <cstring>

import riptide.client.app;
import riptide.utils.logging;

auto main() -> int {
    try {
        riptide::client::app::App app;
        app.run();
    } catch (const std::exception &e) {
        riptide::utils::logging::fatal("{}: {}", e.what(), std::strerror(errno));
    }

    return 0;
}