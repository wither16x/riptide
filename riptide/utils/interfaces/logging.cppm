module;
#include <std.h>

export module riptide.utils.logging;

namespace riptide::utils::logging {

constexpr const std::string COLOR_RESET = "\33[0m";
constexpr const std::string COLOR_CYAN = "\33[1;36m";
constexpr const std::string COLOR_GREEN = "\33[1;32m";
constexpr const std::string COLOR_YELLOW = "\33[1;33m";
constexpr const std::string COLOR_RED = "\033[1;31m";
constexpr const std::string COLOR_PURPLE = "\033[1;35m";
constexpr const std::string COLOR_GRAY = "\33[0;90m";

export enum class LogLevel {
    Debug, //< Information for the programmer
    Info, //< Information for the user and the programmer
    Ok, //< Operation successfull
    Warn, //< Something not recommended happened
    Err, //< Operation failed
    Fatal //< Everything has been fucked up
};

auto log_level_to_string(LogLevel level) -> const std::string;

/**
 * @brief Display a log with the full current time, a colorful log type and a
 * formattable message.
 *
 * @param level log level
 * @param fmt message to format
 * @param args arguments to format the message
 */
export template<typename... Args>
auto log(LogLevel level, std::format_string<Args...> fmt, Args &&...args) -> void {
    std::string level_str = log_level_to_string(level);
    std::string time = std::format("{:%F %T %Z}", std::chrono::zoned_time{
        std::chrono::current_zone(),
        std::chrono::system_clock::now()
    });
    auto formatted = std::format(fmt, std::forward<Args &&>(args)...);
    std::println("{}[{}]{} {}: {}", COLOR_GRAY, time, COLOR_RESET, level_str, formatted);
}

export template<typename... Args>
auto debug(std::format_string<Args...> fmt, Args &&...args) -> void {
    log(LogLevel::Debug, fmt, std::forward<Args &&>(args)...);
}

export template<typename... Args>
auto info(std::format_string<Args...> fmt, Args &&...args) -> void {
    log(LogLevel::Info, fmt, std::forward<Args &&>(args)...);
}

export template<typename... Args>
auto ok(std::format_string<Args...> fmt, Args &&...args) -> void {
    log(LogLevel::Ok, fmt, std::forward<Args &&>(args)...);
}

export template<typename... Args>
auto warn(std::format_string<Args...> fmt, Args &&...args) -> void {
    log(LogLevel::Warn, fmt, std::forward<Args &&>(args)...);
}

export template<typename... Args>
auto err(std::format_string<Args...> fmt, Args &&...args) -> void {
    log(LogLevel::Err, fmt, std::forward<Args &&>(args)...);
}

export template<typename... Args>
auto fatal(std::format_string<Args...> fmt, Args &&...args) -> void {
    log(LogLevel::Fatal, fmt, std::forward<Args &&>(args)...);
}

} // namespace riptide::utils::logging