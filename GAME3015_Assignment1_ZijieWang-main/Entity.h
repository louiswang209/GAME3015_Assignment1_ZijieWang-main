//GAME3015-Assignment1-Zijie Wang
//Name:Zijie Wang
//ID:101283316
//Last Updated: 2/2/2022
#pragma once
#include "SceneNode.h"
#include "FrameResource.h"

/// <summary>
/// Main class for most objects in game world
/// </summary>
class Entity	:
	public SceneNode
{
	friend class World;

public:
	Entity();
	~Entity();
		
protected:
	float	m_MoveSpeed;

public:
	virtual void Update(float DeltaTime, struct FrameResource* Frame);
	virtual void Draw(ID3D12GraphicsCommandList* CmdList, float DeltaTime);
};

