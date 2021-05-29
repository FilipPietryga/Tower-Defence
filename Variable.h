#pragma once
#include "Type.h"

template <typename T>
class Variable
{
public:
	Variable();
	Variable(const Type&, const T&);
private:
	Type type;
	T value;
};

