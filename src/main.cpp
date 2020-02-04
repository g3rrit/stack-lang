#include "log.hpp"
#include "parser.hpp"
#include "err.hpp"
#include "syntax.hpp"
#include "eval.hpp"
#include "util.hpp"

#include <fstream>

const std::string VERSION = "0.1.1";

auto main(int argc, char **argv) -> int 
{
	if (argc <= 1) {
		log::log("usage: stack-lang file");
		return 0;
	}

	log::log("-- STACK LANG", VERSION, "--");

	parser p { argv[1] };

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
		}
	} catch (err& e) {
		log::log("PARSER ERROR:", e.what());
		return 0;
	}

	log::log("<< RUNNING >>");

	try {
		v.run();
	} catch (std::exception& e) {
		log::log("RUNTIME ERROR:", e.what());
		return 0;
	}

	log::log("<< DONE >>");

	return 0;
}
