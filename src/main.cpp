#include "log.hpp"
#include "parser.hpp"
#include "err.hpp"
#include "generator.hpp"
#include "syntax.hpp"
#include "eval.hpp"

#include <fstream>

const std::string VERSION = "0.0.1";

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
			ins i = p.next();
			if (std::get<0>(*i) == tag::END) {
				v.add(std::move(i));
				break;
			}
			v.add(std::move(i));
		}
	} catch (err& e) {
		log::log("error:", e.what());
	}

	v.run();

	log::log("done!");

	return 0;
}
