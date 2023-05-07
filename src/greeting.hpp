#ifndef GREETING_HPP
#define GREETING_HPP

#include <fmt/ostream.h>

#include <iostream>
#include <string>

namespace hello {

struct greeting {
    std::string name{};
    friend auto operator<<(std::ostream& out, const greeting& obj) -> std::ostream&;
};

}  // namespace hello

template <>
struct fmt::formatter<hello::greeting> : ostream_formatter {};

#endif  // GREETING_HPP
