#pragma once
class Stripper
{
public:
	Stripper(const std::string&, const std::string&);
	~Stripper();
public:
	std::string strip();
private:
	std::string _string;
	char _separator = ' ';
};

