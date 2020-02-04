#ifndef EVAL_HPP
#define EVAL_HPP

#include <vector>
#include <map>

#include "syntax.hpp"

struct vm 
{
	std::vector<ins> txt;
	std::vector<int> stack;
	std::map<std::string, int> lmap;

	int pos = 0;

	auto add(ins i) -> void;
	auto add_label(const std::string l) -> void;
	
	auto run() -> void;

	auto eval_psh(int num) -> void;
	auto eval_pop(int num) -> void;
	auto eval_jnz(const std::string& id) -> void;
	auto eval_dup(int num) -> void;
	auto eval_swp() -> void;
	auto eval_add() -> void;
	auto eval_mul() -> void;
	auto eval_prt() -> void;
	auto eval_sze() -> void;
	auto eval_jmp(const std::string& id) -> void;
};

#endif
