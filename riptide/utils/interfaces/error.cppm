module;
#include <std.h>

export module riptide.utils.error;

namespace riptide::utils::error {

export class RiptideException : public std::exception {
public:
    RiptideException(const std::string &msg);

    auto what() const noexcept -> const char *;

private:
    std::string msg_;
};

} // namespace riptide::utils::error