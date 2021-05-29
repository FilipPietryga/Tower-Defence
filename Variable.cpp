#include "Variable.h"

template<typename T>
Variable<T>::Variable()
{

}

template<typename T>
Variable<T>::Variable(const Type& type, const T& value)
{
	this->type = type;
	this->value = value;
}