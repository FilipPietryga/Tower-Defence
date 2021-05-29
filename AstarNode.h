#pragma once
class AStarNode
{
public:
	AStarNode(int x, int y);
	int _x, _y;
	AStarNode* parent;
	float g, h, f;
};