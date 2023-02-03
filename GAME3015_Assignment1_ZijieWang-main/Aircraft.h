//GAME3015-Assignment1-Zijie Wang
//Name:Zijie Wang
//ID:101283316
//Last Updated: 2/2/2022

#pragma once

#include "Entity.h"

/// <summary>
/// Enemy class, derived from Entity
/// </summary>
class Aircraft	:
	public Entity
{
public:
	Aircraft();
	~Aircraft();

private:
	float	m_Dir;

public:
	virtual void Update(float DeltaTime, struct FrameResource* Frame);
	virtual void Draw(ID3D12GraphicsCommandList* CmdList, float DeltaTime);
};

