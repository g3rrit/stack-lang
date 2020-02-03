#include "log.hpp"
#include "parser.hpp"
#include "err.hpp"
#include "generator.hpp"
#include "syntax.hpp"
#include "eval.hpp"
#include "util.hpp"

#include <fstream>

const std::string VERSION = "0.1.1";

namespace test {
	void test();
}

auto main() -> int 
{
	log::log("-- STACK LANG COMPILER", VERSION, "--");

	parser p { "../example/fib.sl" };

	vm v;

	try {
		for (;;) {
			token t = p.next();
			if (std::holds_alternative<std::string>(t)) {
				v.add_label(std::move(std::get<std::string>(t)));
			} else if (std::holds_alternative<ins>(t)) {
				v.add(std::move(std::get<ins>(t)));
			} else if (std::holds_alternative<std::monostate>(t)) {
				break;
			}
			/*
			if (std::get<0>(*i) == tag::END) {
				v.add(std::move(i));
				break;
			}
			v.add(std::move(i));
			*/
		}
	} catch (err& e) {
		log::log("error:", e.what());
	}

	log::log("running vm");

	try {
		v.run();
	} catch (std::exception& e) {
		log::log("error:", e.what());
	}

	log::log("done!");

	return 0;
}
