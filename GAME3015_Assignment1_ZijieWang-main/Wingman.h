//GAME3015-Assignment1-Phu-Pham
//10/2/2022
//Name: Phu Pham
//ID: 101250748

#pragma once
#include "Entity.h"
#include "Common/d3dUtil.h"
#include "Common/GameTimer.h"
class Wingman : public Entity
{
private:
	bool right = true;
public:
	Wingman() {};
	Wingman(XMFLOAT3 position, XMFLOAT3 scale);
	void Move(const GameTimer& gt);

	void Update(const GameTimer& gt);
};