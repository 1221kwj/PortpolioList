#pragma once
#include "Mesh.h"

class MeshSphere : public Mesh
{
public:
	MeshSphere( Material* material, float radius = 1.0f, UINT stackCount = 10, UINT sliceCount = 10 );
	~MeshSphere();

	void CreateData() override;

private:
	float radius;

	UINT stackCount;
	UINT sliceCount;
};