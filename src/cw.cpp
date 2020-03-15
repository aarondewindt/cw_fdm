//
// Created by adewindt on 3/8/20.
//

#include <cw.hpp>
#include <typeinfo>


#if __has_include(<cxxabi.h>)
    #include <cxxabi.h>
    #include <memory>
namespace cw {
    std::string get_type_name(const std::type_info& type_info) {
        const char* name = type_info.name();
        int status = -4; // some arbitrary value to eliminate the compiler warning

        // enable c++11 by passing the flag -std=c++11 to g++
        std::unique_ptr<char, void(*)(void*)> res {
                abi::__cxa_demangle(name, NULL, NULL, &status),
                std::free
        };
        return (status==0) ? res.get() : name ;
    }
}
#else
namespace cw {
    std::string get_type_name(const std::type_info& type_info) {
        return type_info.name();
    }
}
#endif





