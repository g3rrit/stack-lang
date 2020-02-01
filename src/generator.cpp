#include "generator.hpp"

#include "log.hpp"

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
