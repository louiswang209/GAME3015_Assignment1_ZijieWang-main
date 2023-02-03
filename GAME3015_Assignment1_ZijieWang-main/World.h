//GAME3015-Assignment1-Zijie Wang
//Name:Zijie Wang
//ID:101283316
//Last Updated: 2/2/2022
#pragma once

#include "Entity.h"
#include "Player.h"
#include "Aircraft.h"


/// <summary>
/// Handles all objects that are built in World
/// </summary>

class World
{
public:
	World();
	~World();

public:
	SceneNode* m_RootNode;

	std::map<std::string, std::unique_ptr<Material>> mMaterials;
	std::list<SceneNode*>	m_RenderList;
	std::unique_ptr<MeshGeometry>	m_Mesh;

	//Terrain 
	Entity* Terrain1= new Entity;
	Entity* Terrain2 = new Entity;
	//Wingman
	Entity* Wingman1 = new Player;
	Entity* Wingman2 = new Player;
	//Enemy
	Aircraft* Enemy = new Aircraft;
	//Player
	Player* player = new Player;


	void Build(ID3D12Device* Device, ID3D12GraphicsCommandList* CmdList);

	void Update(float DeltaTime, struct FrameResource* Frame);
	void Draw(ID3D12GraphicsCommandList* CmdList, ID3D12DescriptorHeap* Desc,
		UINT DescSize, struct FrameResource* Frame, float DeltaTime);
};

