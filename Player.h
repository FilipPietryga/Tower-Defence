#pragma once
class Player
{
public:
	Player()
		: _health(1), _money(0)
	{   }
	Player(int health, int money)
		: _health(health), _money(money)
	{	}
	Player& setHealth(int health)
	{
		_health = health;
		return *this;
	}
	Player& setMoney(int money)
	{
		_money = money;
		return *this;
	}
	int _health;
	int _money;
};