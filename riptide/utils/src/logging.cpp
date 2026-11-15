module;
#include <std.h>

module riptide.utils.logging;

namespace riptide::utils::logging {

auto log_level_to_string(LogLevel level) -> const std::string {
    switch (level) {
    case LogLevel::Debug:
        return COLOR_GRAY + "DEBUG" + COLOR_RESET;
    case LogLevel::Info:
        return COLOR_CYAN + "INFO" + COLOR_RESET;
    case LogLevel::Ok:
        return COLOR_GREEN + "OK" + COLOR_RESET;
    case LogLevel::Warn:
        return COLOR_YELLOW + "WARNING" + COLOR_RESET;
    case LogLevel::Err:
        return COLOR_RED + "ERROR" + COLOR_RESET;
    case LogLevel::Fatal:
        return COLOR_PURPLE + "FATAL" + COLOR_RESET;
    }
}

} // namespace riptide::utils::logging