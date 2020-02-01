#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>

struct generator 
{

	auto handle_psh(int num) -> void;
	auto handle_pop() -> void;
	auto handle_jnz(const std::string& id) -> void;
	auto handle_dup(int num) -> void;
	auto handle_swp() -> void;
	auto handle_add() -> void;
	auto handle_mul() -> void;
	auto handle_jmp(const std::string& id) -> void;
	auto handle_label(const std::string& id) -> void;
};

#endif
