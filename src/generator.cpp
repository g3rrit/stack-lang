#include "generator.hpp"

#include "log.hpp"

auto generator::handle(ins i) -> void 
{
	auto& [t, v] = *i;

	switch (t) {
		case tag::PSH:
			handle_psh(std::get<int>(v));
			break;
		case tag::POP:
			handle_pop();
			break;
		case tag::JNZ:
			handle_jnz(std::get<std::string>(v));
			break;
		case tag::DUP:
			handle_dup(std::get<int>(v));
			break;
		case tag::SWP:
			handle_swp();
			break;
		case tag::ADD:
			handle_add();
			break;
		case tag::MUL:
			handle_mul();
			break;
		case tag::JMP:
			handle_jmp(std::get<std::string>(v));
			break;
		case tag::LABEL:
			handle_label(std::get<std::string>(v));
			break;
	}
}

auto generator::handle_psh(int num) -> void 
{
	log::log("psh", num);	
}

auto generator::handle_pop() -> void 
{
	log::log("pop");	
}

auto generator::handle_jnz(const std::string& id) -> void 
{
	log::log("jnz", id);	
}

auto generator::handle_dup(int num) -> void 
{
	log::log("dup", num);	
}

auto generator::handle_swp() -> void 
{
	log::log("swp");	
}

auto generator::handle_add() -> void 
{
	log::log("add");	
}

auto generator::handle_mul() -> void 
{
	log::log("mul");	
}

auto generator::handle_jmp(const std::string& id) -> void 
{
	log::log("jmp", id);	
}

auto generator::handle_label(const std::string& id) -> void 
{
	log::log("label", id);	
}
