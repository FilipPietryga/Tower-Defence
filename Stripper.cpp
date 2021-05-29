#include "pch.h"
#include "Stripper.h"

Stripper::Stripper(const std::string& string, const std::string& separator)
{	
	_string = string;
	_separator = separator[0];
}

std::string Stripper::strip() 
{
	std::string buffer = this->_string;
	std::string value = "";
	for (unsigned int i = 0; i < buffer.length(); i++) 
	{
		if (buffer[i] == _separator)
		{
			buffer.erase(0, i + 1);
			this->_string = buffer;
			return value;
		}
		value += buffer[i];
	}
	return value;
}

Stripper::~Stripper()
{
	
}