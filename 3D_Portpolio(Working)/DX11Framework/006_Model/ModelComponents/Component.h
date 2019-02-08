#pragma once

#include "stdafx.h"

enum class COMPONENTTYPEID
{
	TYPEID_NONE = 0	,
	TYPEID_TRANSFORM,
	TYPEID_MATERIAL	,
	TYPEID_MESH		,
	TYPEID_BONE		,
};

class Component
{
public:
	Component();
	virtual ~Component();

	wstring			GetTypeName();
	void			SetTypeName( wstring name );

	COMPONENTTYPEID	GetTypeID();
	void			SetTypeID( COMPONENTTYPEID id );

	bool			GetVisible();
	void			SetVisible( bool v );
	vector<function<void( bool )>> Visibled;

	bool			GetEnable();
	void			SetEnable( bool e );
	vector<function<void( bool )>> Enabled;

private:
	wstring			typeName;
	COMPONENTTYPEID	typeID;

	bool			bVisible;
	bool			bEnable;
};