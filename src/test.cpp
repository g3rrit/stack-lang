#include "log.hpp"

#include "err.hpp"
#include "parser.hpp"
#include <stdio.h>

namespace test {

	auto erf() 
	{
		throw err("test error");
	}


	void test_desc();

	auto test() 
	{
		log::log("test");

		try {
			erf();
		} catch (std::exception& e) {
			log::log(e.what());
		}

		// test parser
		

	}


}
