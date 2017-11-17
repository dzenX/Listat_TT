#pragma once

#include <string>

class descriptive_exception : public std::exception {
public:
	descriptive_exception(std::string const &message) : msg_(message) { }
	virtual char const *what() const noexcept { return msg_.c_str(); }
private:
	std::string msg_;
};
