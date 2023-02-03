//GAME3015-Assignment1-Zijie Wang
//Name:Zijie Wang
//ID:101283316
//Last Updated: 2/2/2022
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}
/// <summary>
/// Handles player movement
/// </summary>
void Player::Update(float DeltaTime, FrameResource* Frame)
{
	// W key for moving up
	if (d3dUtil::IsKeyDown(0x57))
	{
		m_Pos.z += 0.5f;
	}

	// A key for moving left
	if (d3dUtil::IsKeyDown(0x41))
	{
		m_Pos.x -= 0.5f;
	}

	// S key for moving down
	if (d3dUtil::IsKeyDown(0x53))
	{
		m_Pos.z -= 0.5f;
	}

	// D key for moving right
	if (d3dUtil::IsKeyDown(0x44))
	{
		m_Pos.x += 0.5f;
	}
	Entity::Update(DeltaTime, Frame);
}

void Player::Draw(ID3D12GraphicsCommandList* CmdList, float DeltaTime)
{
	Entity::Draw(CmdList, DeltaTime);
}
