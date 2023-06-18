/*
 * Copyright (c) 2021 Robert Nystrom
 * Copyright (c) 2023 David Holmes
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "chunk.hpp"
#include "memory.hpp"

namespace lox {

void Chunk::write(std::uint8_t byte, int line)
{
    bytes_.push_back(byte);
    lines_.push_back(line);
}

int Chunk::addConstant(Value value)
{
    constants_.push_back(value);
    return constants_.size() - 1;
}

}  // namespace lox
