#pragma once

class ModelMesh
{
public:
	friend class Model;
	friend class Models;
	friend class ModelMeshes;

public:
	void Render();
	
	wstring Name()						{ return name; }
	
	int ParentBoneIndex()				{ return parentBoneIndex; }
	
	class ModelBone* ParentBone()		{ return parentBone; }

public:
	void Clone( ModelMesh** clone );

private:
	void Binding();

private:
	ModelMesh();
	~ModelMesh();

	wstring							name;

	int								parentBoneIndex;
	class ModelBone*				parentBone;

	vector<class ModelMeshPart *>	meshParts;
};