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


	LABEL,

	END,
};


typedef std::variant<int, std::string, std::monostate> var;
typedef std::unique_ptr<std::pair<tag, var>> ins;

#endif
