#ifndef ERR_HPP
#define ERR_HPP

#include <exception>
#include <string>

struct err : std::exception {
	std::string _what;

	err(std::string&& what);
	err(std::string& what);

	auto what() const noexcept -> const char* override;
};

#endif
