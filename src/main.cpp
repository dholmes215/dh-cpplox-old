#include "greeting.hpp"

#include <fmt/format.h>

auto main() -> int
{
    fmt::print("{}\n", hello::greeting{"World"});
}
