/*
 * Copyright (c) 2021 Robert Nystrom
 * Copyright (c) 2023 David Holmes
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "chunk.hpp"
#include "debug.hpp"

#include <gsl/narrow>

namespace lox {

/**
 * @brief Convert enumeration to its underlying type.
 * TODO: In C++23, replace this with std::to_underlying.
 *
 * @param enum_value An enumeration value.
 * @return The integer value of the underlying type of the enum, converted from
 * enum_value.
 */
auto to_underlying(auto enum_value)
{
    using Enum = decltype(enum_value);
    return static_cast<std::underlying_type_t<Enum>>(enum_value);
}

int main()
{
    Chunk chunk;

    // TODO: Instead of cast, support constant pool larger than 256, as per
    // "challenges" section
    auto constant{gsl::narrow<std::uint8_t>(chunk.addConstant(1.2))};
    chunk.write(to_underlying(Op::constant), 123);
    chunk.write(constant, 123);

    chunk.write(to_underlying(Op::return_), 123);

    disassembleChunk(chunk, "test chunk");

    return 0;
}

}  // namespace lox

int main()
{
    return lox::main();
}
