/*
 * Copyright (c) 2021 Robert Nystrom
 * Copyright (c) 2023 David Holmes
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#ifndef CPPLOX_VM_HPP
#define CPPLOX_VM_HPP

#include "chunk.hpp"

namespace lox {

enum class InterpretResult { ok, compile_error, runtime_error };

class VM {
    using InstructionPointer = ByteArray::const_iterator;

   public:
    InterpretResult interpret(Chunk* chunk);

   private:
    Chunk* chunk_{nullptr};
    InstructionPointer ip_{};
};

}  // namespace lox

#endif  // CPPLOX_VM_HPP
