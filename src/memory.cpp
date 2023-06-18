/*
 * Copyright (c) 2021 Robert Nystrom
 * Copyright (c) 2023 David Holmes
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "memory.hpp"

#include <cstdint>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace lox {

malloc_error::malloc_error(std::size_t size) noexcept : alloc_error{}
{
    std::format_to_n(what_.begin(), what_.size(), "malloc failed, size: {}",
                     size);
}

calloc_error::calloc_error(std::size_t num, std::size_t size) noexcept
    : alloc_error{}
{
    std::format_to_n(what_.begin(), what_.size(),
                     "calloc failed, num: {} size: {}", num, size);
}

realloc_error::realloc_error(std::size_t size) noexcept : alloc_error{}
{
    std::format_to_n(what_.begin(), what_.size(), "realloc failed, size: {}",
                     size);
}

void malloc_ptr::realloc(std::size_t size)
{
    void* newptr{std::realloc(ptr_, size)};
    if (!newptr) {
        throw realloc_error{size};
    }
    ptr_ = newptr;
}

malloc_ptr make_malloc(std::size_t size)
{
    void* ptr{std::malloc(size)};
    if (!ptr) {
        throw malloc_error{size};
    }
    return malloc_ptr{ptr};
}

malloc_ptr make_calloc(std::size_t num, std::size_t size)
{
    void* ptr{std::calloc(num, size)};
    if (!ptr) {
        throw calloc_error{num, size};
    }
    return malloc_ptr{ptr};
}

}  // namespace lox
