module;
#include <std.h>
#include <cstring>
#include <cerrno>

module riptide.utils.error;

namespace riptide::utils::error {

RiptideException::RiptideException(const std::string &msg)
    : msg_(msg)
{}

auto RiptideException::what() const noexcept -> const char * {
    return msg_.c_str();
}

} // namespace riptide::utils::error