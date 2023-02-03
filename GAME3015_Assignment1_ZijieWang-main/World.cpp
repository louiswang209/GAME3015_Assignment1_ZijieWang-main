//GAME3015-Assignment1-Zijie Wang
//Name:Zijie Wang
//ID:101283316
//Last Updated: 2/2/2022
#include "World.h"
#include <iostream>

World::World()
{
}

World::~World()
{
	delete	m_RootNode;
}

/// <summary>
/// Build all objects in game world
/// </summary>
void World::Build(ID3D12Device* Device, ID3D12GraphicsCommandList* CmdList)
{
	m_RootNode = new SceneNode;

	GeometryGenerator geoGen;

	GeometryGenerator::MeshData Quad = geoGen.CreateQuad(-0.5f, 0.5f, 1.f, 1.f, 0.f);
	UINT gridVertexOffset = 0;
	UINT gridIndexOffset = 0;
	SubmeshGeometry QuadSubmesh;
	QuadSubmesh.IndexCount = (UINT)Quad.Indices32.size();
	QuadSubmesh.StartIndexLocation = gridIndexOffset;
	QuadSubmesh.BaseVertexLocation = gridVertexOffset;

	auto totalVertexCount =
		Quad.Vertices.size();

	std::vector<Vertex> vertices(totalVertexCount);

	UINT k = 0;
	for (size_t i = 0; i < Quad.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = Quad.Vertices[i].Position;
		vertices[k].Normal = Quad.Vertices[i].Normal;
		vertices[k].TexC = Quad.Vertices[i].TexC;
	}

	std::vector<std::uint16_t> indices;

	indices.insert(indices.end(), std::begin(Quad.GetIndices16()), std::end(Quad.GetIndices16()));

	const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

	m_Mesh = std::make_unique<MeshGeometry>();
	m_Mesh->Name = "Quad";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &m_Mesh->VertexBufferCPU));
	CopyMemory(m_Mesh->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &m_Mesh->IndexBufferCPU));
	CopyMemory(m_Mesh->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	m_Mesh->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(Device,
		CmdList, vertices.data(), vbByteSize, m_Mesh->VertexBufferUploader);

	m_Mesh->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(Device,
		CmdList, indices.data(), ibByteSize, m_Mesh->IndexBufferUploader);


	m_Mesh->VertexByteStride = sizeof(Vertex);
	m_Mesh->VertexBufferByteSize = vbByteSize;
	m_Mesh->IndexFormat = DXGI_FORMAT_R16_UINT;
	m_Mesh->IndexBufferByteSize = ibByteSize;

	m_Mesh->DrawArgs["Quad"] = QuadSubmesh;

	// Terrain
	Terrain1->m_Pos = XMFLOAT3(0.f, 0.f, 0.f);
	Terrain1->m_Scale = XMFLOAT3(115.f, 130.f, 1.f);
	Terrain1->m_Rot = XMFLOAT3(3.14159f / 2.f, 0.f, 0.f);
	Terrain1->m_MBIndex = 0;
	Terrain1->m_TexIndex = 0;
	m_RootNode->AddChild(Terrain1);
	m_RenderList.push_back(Terrain1);

	Terrain2->m_Pos = XMFLOAT3(0.f, 0.f, 116.f);
	Terrain2->m_Scale = XMFLOAT3(115.f, 130.f, 1.f);
	Terrain2->m_Rot = XMFLOAT3(3.14159f / 2.f, 0.f, 0.f);
	Terrain2->m_MBIndex = 0;
	Terrain2->m_TexIndex = 0;
	m_RootNode->AddChild(Terrain2);
	m_RenderList.push_back(Terrain2);

	// PLAYER character
	player->m_Pos = XMFLOAT3(0.f, 10.f, -10.f);
	player->m_Scale = XMFLOAT3(10.f, 10.f, 1.f);
	player->m_Rot = XMFLOAT3(3.14159f / 2.f, 0.f, 0.f);
	player->m_MBIndex = 1;
	player->m_TexIndex = 1;
	m_RootNode->AddChild(player);
	m_RenderList.push_back(player);


	// ENEMY Character
	Enemy->m_Pos = XMFLOAT3(0.f, 10.f, 15.f);
	Enemy->m_Scale = XMFLOAT3(5.f, 5.f, 1.f);
	Enemy->m_Rot = XMFLOAT3(3.14159f / 2.f, 0.f, 0.f);
	Enemy->m_MBIndex = 2;
	Enemy->m_TexIndex = 2;
	m_RootNode->AddChild(Enemy);
	m_RenderList.push_back(Enemy);

	// WINGMAN1 Character
	Wingman1->m_Pos = XMFLOAT3(-10.f, 10.f, -15.f);
	Wingman1->m_Scale = XMFLOAT3(5.f, 5.f, 1.f);
	Wingman1->m_Rot = XMFLOAT3(3.14159f / 2.f, 0.f, 0.f);
	Wingman1->m_MBIndex = 3;
	Wingman1->m_TexIndex = 1;
	player->AddChild(Wingman1);
	m_RenderList.push_back(Wingman1);

	// WINGMAN2 Character
	Wingman2->m_Pos = XMFLOAT3(10.f, 10.f, -15.f);
	Wingman2->m_Scale = XMFLOAT3(5.f, 5.f, 1.f);
	Wingman2->m_Rot = XMFLOAT3(3.14159f / 2.f, 0.f, 0.f);
	Wingman2->m_MBIndex = 3;
	Wingman2->m_TexIndex = 1;
	player->AddChild(Wingman2);
	m_RenderList.push_back(Wingman2);

}

/// <summary>
/// Update root node and scroll the background
/// </summary>
void World::Update(float DeltaTime, struct FrameResource* Frame)
{
	m_RootNode->m_GlobalCBIndex = 0;
	m_RootNode->Update(DeltaTime, Frame);
	int m_Direction = -1.f;
	Terrain1->m_Pos.z += 20.f * m_Direction * DeltaTime;
	Terrain2->m_Pos.z += 20.f * m_Direction * DeltaTime;

	if (Terrain1->m_Pos.z < -125)
	{
		Terrain1->m_Pos.z = 120;
	}
	if (Terrain2->m_Pos.z < -125)
	{
		Terrain2->m_Pos.z = 120;
	}

}

/// <summary>
/// Draw all objects in game world
/// </summary>
void World::Draw(ID3D12GraphicsCommandList* CmdList, ID3D12DescriptorHeap* Desc,
	UINT DescSize, struct FrameResource* Frame, float DeltaTime)
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = Frame->ObjectCB->Resource();
	auto matCB = Frame->MaterialCB->Resource();

	auto	iter = m_RenderList.begin();
	auto	iterEnd = m_RenderList.end();

	for (; iter != iterEnd; ++iter)
	{
		CmdList->IASetVertexBuffers(0, 1, &m_Mesh->VertexBufferView());
		CmdList->IASetIndexBuffer(&m_Mesh->IndexBufferView());
		CmdList->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(
			Desc->GetGPUDescriptorHandleForHeapStart()
			);

		tex.Offset((*iter)->GetTexIndex(), DescSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + (*iter)->m_CBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + (*iter)->m_MBIndex * matCBByteSize;

		CmdList->SetGraphicsRootDescriptorTable(0, tex);
		CmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
		CmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

		CmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
	}
}
