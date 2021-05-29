#include "pch.h"
#include "ArgumentException.h"

ArgumentException::ArgumentException()
	: Exception("Argument Exception")
{	
	_filename = nullptr;
	_line = 0;
	_func = nullptr;
	_info = nullptr;
	_varName = nullptr;
	_varType = nullptr;
}

ArgumentException ArgumentException::setFilename(const char* filename) {
	_filename = filename;
	return *this;
}

ArgumentException ArgumentException::setLine(const int& line) {
	_line = line;
	return *this;
}

ArgumentException ArgumentException::setFunc(const char* func) {
	_func = func;
	return *this;
}

ArgumentException ArgumentException::setInfo(const char* info) {
	_info = info;
	return *this;
}

ArgumentException ArgumentException::setVarType(const char* varType) {
	_varType = varType;
	return *this;
}

ArgumentException ArgumentException::setVarName(const char* varName) {
	_varName = varName;
	return *this;
}

const char* ArgumentException::getVariableName()
{
	return _varName;
}

const char* ArgumentException::getVariableType()
{
	return _varType;
}

const char* ArgumentException::what() const throw()
{
	std::stringstream ss;

	ss << "Argument Exception\n\tin file: " << _filename
		<< "\n\tin function: " << _func
		<< "\n\tin line: " << _line
		<< "\n\tin variable: " << _varName 
		<< "\n\tof type: " << _varType
		<< "\n\tmore info: " << _info << std::endl;
	
	std::string result = ss.str();

	std::cerr << result.c_str() << std::endl;

	return result.c_str();
}