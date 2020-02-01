#ifndef UTIL_HPP
#define UTIL_HPP

// VARIANT HELPER
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

#endif
