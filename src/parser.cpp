#include "parser.hpp"
#include "err.hpp"

#include <cstdlib>

const unsigned int MAX_STR_LEN = 256;

// checks if char is 0 .. 9
bool is_num(char _c) 
{
	return (_c >= '0' && _c <= '9');
}

bool is_num_start(char _c) 
{
	return (is_num(_c) || _c == '+' || _c == '-');
}

// checks if char is a .. z | A .. Z | _
bool is_alpha(char _c) 
{
  	return ((_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z') || _c == '_');
}

// checks if char is a .. z | A .. Z | 0 .. 9 | _
bool is_alpha_num(char _c) 
{
  	return ((_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z') || (_c >= '0' && _c <= '9') || _c == '_');
}

// checks if character is to be ignored
bool is_white(char _c) 
{
	return (_c == ' ' || _c == '\t' || _c == '\n');
}

parser::parser(const std::string& path) 
	: is(path) {}

auto parser::next() -> token 
{
	_white();
	int c = is.peek();
	if (c == EOF) {
		return std::monostate();
		//return std::make_unique<std::pair<tag, var>>(tag::END, std::monostate());
	}

	if (!is_alpha(c)) {
		throw err("parser error");
	}
	
	std::string id = parse_id();

	if        (id == "psh") {
		int v = parse_int();
		return std::make_unique<std::pair<tag, var>>(tag::PSH, v);
	} else if (id == "pop")  {
		return std::make_unique<std::pair<tag, var>>(tag::POP, std::monostate());
	} else if (id == "jnz")  {
		std::string label = parse_id();
		return std::make_unique<std::pair<tag, var>>(tag::JNZ, std::move(label));
	} else if (id == "dup")  {
		int v = parse_int();
		return std::make_unique<std::pair<tag, var>>(tag::DUP, v);
	} else if (id == "swp") {
		return std::make_unique<std::pair<tag, var>>(tag::SWP, std::monostate());
	} else if (id == "add")  {
		return std::make_unique<std::pair<tag, var>>(tag::ADD, std::monostate());
	} else if (id == "mul")  {
		return std::make_unique<std::pair<tag, var>>(tag::MUL, std::monostate());
	} else if (id == "prt")  {
		return std::make_unique<std::pair<tag, var>>(tag::PRT, std::monostate());
	} else if (id == "sze")  {
		return std::make_unique<std::pair<tag, var>>(tag::SZE, std::monostate());
	} else {
		if (is.peek() == ':') { // label
			is.get();
			return std::move(id);
			//return std::make_unique<std::pair<tag, var>>(tag::LABEL, std::move(id));
		} else {                // jmp
			return std::make_unique<std::pair<tag, var>>(tag::JMP, std::move(id));
		}
	}
}


template <class R, class S, class E, class M>
auto parser::_parse(const char* errs, S s, E e, M m) -> R 
{
	_white();
	int c = is.get();
	if (c == EOF || !s(c)) {
		throw err(errs);
	}

	char buffer[MAX_STR_LEN] = { 0 };
	buffer[0] = static_cast<char>(c);
	
	for (int i = 1; i < MAX_STR_LEN; i++) {
		c = is.peek();
		if (c == EOF || !e(c)) break;
		c = is.get();
		buffer[i] = static_cast<char>(c);
	}

	return m(buffer);
}

auto parser::_white() -> void
{
	while (is_white(is.peek())) {
		is.get();
	}
}

auto parser::parse_id() -> std::string
{
	return _parse<std::string, std::function<bool(char)>, std::function<bool(char)>, std::function<std::string(char*)>>
				("parser error | expected id",
				[](char c) -> bool { return is_alpha(c); }, 
		 		[](char c) -> bool { return is_alpha_num(c); }, 
				[](char* buf) -> std::string { return std::string(buf); });
}

auto parser::parse_int() -> int
{
	return _parse<int, std::function<bool(char)>, std::function<bool(char)>, std::function<int(char*)>>
				("parser error | expected int",
				[](char c) -> bool { return is_num_start(c); }, 
		 		[](char c) -> bool { return is_num(c); }, 
				[](char* buf) -> int { return atoi(buf); });
}

/*
auto parser::parse_id() -> std::string 
{
	int c = is.get();
	if (c == EOF || !is_alpha(c)) {
		throw err("parser error | expected id");
	}

	char buffer[MAX_STR_LEN] = { 0 };
	buffer[0] = static_cast<char>(c);
	
	for (int i = 1; i < MAX_STR_LEN; i++) {
		c = is.peek();
		if (c == EOF || !is_alpha_num(c)) break;
		c = is.get();
		buffer[i] = static_cast<char>(c);
	}

	return std::string(buffer);
}

auto parser::parse_int() -> int 
{
	int c = is.get();
	if (c == EOF || !is_num(c) || c != '+' || c != '-') {
		throw err("parser error | expected num");
	}

	char buffer[MAX_STR_LEN] = { 0 };
	buffer[0] = static_cast<char>(c);

	for (int i = 1; i < MAX_STR_LEN; i++) {
		c = is.peek();
		if (c == EOF || !is_num(c)) break;
		c = is.get();
		buffer[i] = static_cast<char>(c);
	}

	return std::atoi(buffer);
}
*/
