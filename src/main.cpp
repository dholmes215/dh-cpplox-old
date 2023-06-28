/*
 * Copyright (c) 2021 Robert Nystrom
 * Copyright (c) 2023 David Holmes
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"

#include <gsl/narrow>

namespace lox {

VM vm;

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
    vm.interpret(&chunk);

    return 0;
}

}  // namespace lox

int main()
{
    return lox::main();
}
