#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <iostream>
#include <variant>
#include <memory>

enum tag 
{
	PSH,
	POP,
	JNZ,
	DUP,
	SWP,
	ADD,
	MUL,
	JMP,
	PRT,
	SZE,
};

using var = std::variant<int, std::string, std::monostate>;
using ins = std::unique_ptr<std::pair<tag, var>>;

using token = std::variant<std::string, ins, std::monostate>;

#endif
