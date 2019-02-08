#pragma once
#include "stdafx.h"

class ModelBone
{
public:
	friend class Model;
	friend class Models;
	friend class ModelBones;

private:
	ModelBone();
	~ModelBone();

public:
	int Index();

	int ParentIndex();
	ModelBone* Parent();

	UINT ChildCount();
	ModelBone* Child( UINT index );
	vector<ModelBone *>& GetChilds();

	wstring Name();

	XMFLOAT4X4& Local();
	void Local( XMFLOAT4X4& matrix );

	XMFLOAT4X4& Global();
	void Global( XMFLOAT4X4& matrix );

	template <typename T> T* GetComponent( wstring typeName );

private:
	int											index;
	wstring										name;

	int											parentIndex;
	ModelBone*									parent;

	vector<ModelBone *>							childs;

	typedef pair<wstring, class Component*>		Pair;
	unordered_map<wstring, class Component*>	components;

	XMFLOAT4X4									local;
	XMFLOAT4X4									global;

public:
	void Clone( ModelBone** clone );
};

template<typename T> inline T * ModelBone::GetComponent( wstring typeName )
{
	for ( Pair c : components )
	{
		if ( c.first == typeName )
			return ( T* )c.second;
	}

	return NULL;
}
