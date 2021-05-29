#pragma once
#include "Entity.h"

class Moving : public Entity
{
public:
	Moving();
	Moving(const Moving&);
	Moving& operator=(const Moving&);
	~Moving();
	virtual void move();
private:

};

