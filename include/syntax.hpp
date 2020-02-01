#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <iostream>
#include <variant>

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
typedef std::pair<tag, var> token;

#endif
