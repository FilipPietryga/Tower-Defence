#include "pch.h"
#include "FileLoadException.h"

FileLoadException::FileLoadException()
	: RunTimeException("File Load Exception")
{
	_filename = nullptr;
	_line = 0;
	_func = nullptr;
	_info = nullptr;
	_resourcePath = nullptr;
}

FileLoadException FileLoadException::setFilename(const char* filename) {
	_filename = filename;
	return *this;
}

FileLoadException FileLoadException::setLine(const int& line) {
	_line = line;
	return *this;
}

FileLoadException FileLoadException::setFunc(const char* func) {
	_func = func;
	return *this;
}

FileLoadException FileLoadException::setInfo(const char* info) {
	_info = info;
	return *this;
}

FileLoadException FileLoadException::setResourcePath(const char* resourcePath)
{
	_resourcePath = resourcePath;
	return *this;
}

const char* FileLoadException::getResourcePath()
{
	return _resourcePath;
}

const char* FileLoadException::what() const throw()
{
	std::stringstream ss;

	ss << "Argument Exception\n\tin file: " << _filename
		<< "\n\tin function: " << _func
		<< "\n\tin line: " << _line
		<< "\n\twith source to the searched resource: " << _resourcePath
		<< "\n\tmore info: " << _info << std::endl;

	std::string result = ss.str();

	std::cerr << result.c_str() << std::endl;

	return result.c_str();
}