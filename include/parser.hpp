#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <string>
#include <variant>
#include <functional>

#include "syntax.hpp"


struct parser 
{
	std::ifstream is;

	parser(const std::string& path);

	auto next() -> token;

	template <class R, class S, class E, class M>
	auto _parse(const char* errs, S s, E e, M m) -> R;

	auto _white() -> void;

	auto parse_id() -> std::string;

	auto parse_int() -> int;
};

#endif
