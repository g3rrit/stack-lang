#include "err.hpp"

#include "log.hpp"

err::err(std::string&& what) 
	: _what(what) {}

err::err(std::string& what) 
	: _what(what) {}

auto err::what() const noexcept -> const char* 
{
	return _what.c_str();
}
