/*
 * Copyright (c) 2021 Robert Nystrom
 * Copyright (c) 2023 David Holmes
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "vm.hpp"

#include <fmt/format.h>

namespace lox {

InterpretResult VM::interpret(Chunk* chunk)
{
    auto read_byte{[&] { return *ip_++; }};
    auto read_constant{[&] { return chunk_->constants().at(read_byte()); }};
    auto run{[&] {
        for (;;) {
            Op instruction;
            switch (instruction = static_cast<Op>(read_byte())) {
                case Op::constant: {
                    Value constant{read_constant()};
                    printValue(constant);
                    fmt::print("\n");
                    break;
                }
                case Op::return_: {
                    return InterpretResult::ok;
                }
            }
        }
    }};

    chunk_ = chunk;
    ip_ = chunk->code().begin();
    return run();
}

}  // namespace lox
