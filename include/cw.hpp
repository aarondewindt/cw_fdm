//
// Created by adewindt on 3/8/20.
//

#ifndef CW_SIM_CW_HPP
#define CW_SIM_CW_HPP

#include <cstdint>
#include <cstddef>
#include <string>
#include <typeinfo>


// Hack to add Tristan's span implementation to the C++17 standard library.
#include "tcb/span.hpp"
namespace std {
    using tcb::span;
    using tcb::get;
    using tcb::make_span;
    using tcb::as_bytes;
    using tcb::as_writable_bytes;
    using tcb::dynamic_extent;
}


namespace cw {
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using usize = std::size_t;
    using isize = std::ptrdiff_t;

    using f32 = float;
    using f64 = double;

    std::string get_type_name(const std::type_info& type_info);
}

#endif //CW_SIM_CW_HPP
