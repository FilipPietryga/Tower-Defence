#pragma once
#include "Exception.h"
#include "Variable.h"

class ArgumentException : public Exception
{
public:
	ArgumentException();
	ArgumentException setFilename(const char*);
	ArgumentException setLine(const int&);
	ArgumentException setFunc(const char*);
	ArgumentException setInfo(const char*);
	ArgumentException setVarType(const char*);
	ArgumentException setVarName(const char*);
	const char* getVariableName();
	const char* getVariableType();
	const char* what() const throw();
protected:
	const char* _varName;
	const char* _varType;
};