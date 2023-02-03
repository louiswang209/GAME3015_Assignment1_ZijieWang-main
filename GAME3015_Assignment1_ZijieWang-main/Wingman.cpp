//GAME3015-Assignment1-Phu-Pham
//10/2/2022
//Name: Phu Pham
//ID: 101250748



#include "Wingman.h"


Wingman::Wingman(XMFLOAT3 position, XMFLOAT3 scale)
{
	Position = position;
	Scale = scale;
}

void Wingman::Move(const GameTimer& gt)
{

		// W key for moving up
	if (d3dUtil::IsKeyDown(0x57))
	{
		Position.z += 0.5f;
	}

	// A key for moving left
	if (d3dUtil::IsKeyDown(0x41))
	{
		Position.x -= 0.5f;
	}

	// S key for moving down
	if (d3dUtil::IsKeyDown(0x53))
	{
		Position.z -= 0.5f;
	}

	// D key for moving right
	if (d3dUtil::IsKeyDown(0x44))
	{
		Position.x += 0.5f;
	}

}

void Wingman::Update(const GameTimer& gt)
{
	Move(gt);
}
