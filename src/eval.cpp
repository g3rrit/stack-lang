#include "eval.hpp"

#include "log.hpp"
#include "err.hpp"

auto vm::add(ins i) -> void
{
	auto& [t, v] = *i;
	if (t == tag::LABEL) {	
		if (lmap.count(std::get<std::string>(v)) > 0) {
			throw err("label already presend");
		}
		lmap[std::move(std::get<std::string>(v))] = pos;
		return;
	}
	txt.push_back(std::move(i));
}

auto vm::run() -> void 
{
	for (;;) {
		const auto& [t, v] = *txt.at(pos);
		switch (t) {
		case tag::PSH:
			eval_psh(std::get<int>(v));
			break;
		case tag::POP:
			eval_pop();
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
		case tag::JMP:
			eval_jmp(std::get<std::string>(v));
			break;
		}
		pos++;
		if (pos >= txt.size()) {
			break;
		}
	}
}

auto vm::eval_psh(int num) -> void 
{
	log::log("psh", num);	
	stack.push_back(num);
}

auto vm::eval_pop() -> void 
{
	log::log("pop");	
	stack.pop_back();
}

auto vm::eval_jnz(const std::string& id) -> void 
{
	log::log("jnz", id);	
	if (stack.back() != 0) {
		if (lmap.count(id) == 0) {
			throw err("label " + id + " not defined");
		}
		pos = lmap[id];
	}
}

auto vm::eval_dup(int num) -> void 
{
	log::log("dup", num);	
	if (num >= stack.size()) {
		throw err("stack not big enough");
	}
	stack.push_back(stack.at(num));
}

auto vm::eval_swp() -> void 
{
	log::log("swp");
}

auto vm::eval_add() -> void 
{
	log::log("add");	
}

auto vm::eval_mul() -> void 
{
	log::log("mul");	
}

auto vm::eval_jmp(const std::string& id) -> void 
{
	log::log("jmp", id);	
}
