#pragma once
class Exception : public std::exception
{
public:
	Exception(const char*);
	Exception(const char*, const char*, int, const char*, const char*);
	virtual const char* what() const throw();
public:
	const char* getInfo() const;
	const char* getFilename() const;
	int getLine() const;
	const char* getFunc() const;
protected:
	const char* _info;
	const char* _filename;
	int _line;
	const char* _func;
};

