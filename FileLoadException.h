#include "Exception.h"
#include "RunTimeException.h"

#pragma once
class FileLoadException : public RunTimeException
{
public:
	FileLoadException();
	FileLoadException setFilename(const char*);
	FileLoadException setLine(const int&);
	FileLoadException setFunc(const char*);
	FileLoadException setInfo(const char*);
	FileLoadException setResourcePath(const char*);
	const char* getResourcePath();
	const char* what() const throw();
protected:
	const char* _resourcePath;
};