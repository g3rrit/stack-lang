#include "eval.hpp"
#include "log.hpp"
#include "err.hpp"

#include <iostream>

auto vm::add(ins i) -> void
{
	txt.push_back(std::move(i));
}

auto vm::add_label(const std::string l) -> void
{
	if (lmap.count(l) > 0) {
		throw err("label already presend");
	}
	lmap[std::move(l)] = txt.size() - 1;
}

auto vm::run() -> void 
{
	for (;;) {
		if (pos >= txt.size()) {
			break;
		}

		const auto& [t, v] = *txt.at(pos);
		switch (t) {
		case tag::PSH:
			eval_psh(std::get<int>(v));
			break;
		case tag::POP:
			eval_pop(std::get<int>(v));
			break;
		case tag::JNZ:
			eval_jnz(std::get<std::string>(v));
			break;
		case tag::DUP:
			eval_dup(std::get<int>(v));
			break;
		case tag::SWP:
			eval_swp();
			break;
		case tag::ADD:
			eval_add();
			break;
		case tag::MUL:
			eval_mul();
			break;
		case tag::PRT:
			eval_prt();
			break;
		case tag::JMP:
			eval_jmp(std::get<std::string>(v));
			break;
		case tag::SZE:
			eval_sze();
		}
		pos++;
	}
}

auto vm::eval_psh(int num) -> void 
{
	stack.push_back(num);
}

auto vm::eval_pop(int num) -> void 
{
	if (stack.size() <= 0) {
		throw err("unable to pop empty stack");
	}
	for (;num;num--) {
		stack.pop_back();
	}
}

auto vm::eval_jnz(const std::string& id) -> void 
{
	if (stack.size() <= 1) {
		throw err("empty stack");
	}
	if (stack.back() != 0) {
		if (lmap.count(id) == 0) {
			throw err("label " + id + " not defined");
		}
		pos = lmap[id];
	}
}

auto vm::eval_dup(int num) -> void 
{
	if (num >= stack.size()) {
		throw err("stack not big enough to dup elem");
	}
	stack.push_back(stack.at(num));
}

auto vm::eval_swp() -> void 
{
	if (stack.size() <= 1) {
		throw err("unable to swp in empty stack");
	}
	int tmp = stack.back();
	stack[stack.size() - 1] = stack[stack.size() - 2];
	stack[stack.size() - 1] = tmp;
}

auto vm::eval_add() -> void 
{
	if (stack.size() <= 1) {
		throw err("unable to add");
	}
	stack.push_back(stack[stack.size() - 1] + stack[stack.size() - 2]);
}

auto vm::eval_mul() -> void 
{
	if (stack.size() <= 1) {
		throw err("unable to mul");
	}
	stack.push_back(stack[stack.size() - 1] * stack[stack.size() - 2]);
}

auto vm::eval_jmp(const std::string& id) -> void 
{
	if (lmap.count(id) == 0) {
		throw err("label " + id + " not defined");
	}
	pos = lmap[id];
}

auto vm::eval_prt() -> void 
{
	if (stack.size() <= 0) {
		throw err("unable to print empty stack");
	}
	log::log("STACK [", stack.size() - 1, "] |", stack.back());
}

auto vm::eval_sze() -> void
{
	stack.push_back(stack.size());
}
