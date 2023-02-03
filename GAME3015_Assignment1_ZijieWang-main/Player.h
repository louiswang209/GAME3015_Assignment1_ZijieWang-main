//GAME3015-Assignment1-Zijie Wang
//Name:Zijie Wang
//ID:101283316
//Last Updated: 2/2/2022
#pragma once

#include "Entity.h"
/// <summary>
/// Player class, derived from entity
/// </summary>
class Player	:
	public Entity
{
public:
	Player();
	~Player();

public:
	virtual void Update(float DeltaTime, struct FrameResource* Frame);
	virtual void Draw(ID3D12GraphicsCommandList* CmdList, float DeltaTime);
};

