#include <exception>
#include <stdexcept>
#pragma once
class RunTimeException : public std::runtime_error
{
public:
	RunTimeException(char const* const message) throw()
		: std::runtime_error(message)
	{
		_info = nullptr;
		_filename = nullptr;
		_line = 0;
		_func = nullptr;
	}
	virtual char const* what() const throw()
	{
		return exception::what();
	}
protected:
	const char* _info;
	const char* _filename;
	int _line;
	const char* _func;
};

