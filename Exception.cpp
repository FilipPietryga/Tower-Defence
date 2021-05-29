#include "pch.h"
#include "Exception.h"

Exception::Exception(const char* msg)
	: std::exception(msg)
{	
	_filename = nullptr;
	_line = 0;
	_func = nullptr;
	_info = nullptr;
}

Exception::Exception(const char* msg, const char* filename, int line, const char* func, const char* info = "")
	: std::exception(msg), _filename(filename), _line(line), _func(func), _info(info)
{	
	_filename = nullptr;
	_line = 0;
	_func = nullptr;
	_info = nullptr;
}

const char* Exception::what() const throw()
{
	std::stringstream ss;
	ss << "Undefined Exception\n\tin file: " << _filename
		<< "\n\tin function: " << _func
		<< "\n\tin line: " << _line
		<< "\n\tinfo: " << _info;
	return (ss.str()).c_str();
}