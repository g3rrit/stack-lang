#include "log.hpp"
#include "parser.hpp"
#include "err.hpp"
#include "generator.hpp"

#include <fstream>

const std::string VERSION = "0.0.1";

namespace test {
	void test();
}

auto match_token(generator& gen, tag t, const var& v) 
{
	switch (t) {
		case tag::PSH:
			gen.handle_psh(std::get<int>(v));
			break;
		case tag::POP:
			gen.handle_pop();
			break;
		case tag::JNZ:
			gen.handle_jnz(std::get<std::string>(v));
			break;
		case tag::DUP:
			gen.handle_dup(std::get<int>(v));
			break;
		case tag::SWP:
			gen.handle_swp();
			break;
		case tag::ADD:
			gen.handle_add();
			break;
		case tag::MUL:
			gen.handle_mul();
			break;
		case tag::JMP:
			gen.handle_jmp(std::get<std::string>(v));
			break;
		case tag::LABEL:
			gen.handle_label(std::get<std::string>(v));
			break;
	}
}

auto main() -> int 
{
	log::log("-- STACK LANG COMPILER", VERSION, "--");

	parser p { "../example/fib.sl" };

	generator gen;

	try {
		for (;;) {
			auto [t, v] = p.next();
			if (t == tag::END) break;

			try {
				match_token(gen, t, v);
			} catch (std::exception& e) {
				//log::log("error:", e);
				break;
			}
			
		}
	} catch (err& e) {
		log::log("error:", e.what());
	}

	log::log("done!");

	return 0;
}
