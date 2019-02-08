#include "stdafx.h"
#include "Component.h"

Component::Component()
	: typeName	( L"" )
	, typeID	( COMPONENTTYPEID::TYPEID_NONE )
	, bVisible	( true )
	, bEnable	( true ) 
{
}

Component::~Component()
{
}

wstring Component::GetTypeName()
{
	return typeName;
}

void Component::SetTypeName( wstring name )
{
	typeName = name;
}

COMPONENTTYPEID Component::GetTypeID()
{
	return typeID;
}

void Component::SetTypeID( COMPONENTTYPEID id )
{
	typeID = id;
}

bool Component::GetVisible()
{
	return bVisible;
}

void Component::SetVisible( bool v )
{
	bVisible = v;

	for ( auto temp : Visibled )
		temp( v );
}

bool Component::GetEnable()
{
	return bEnable;
}

void Component::SetEnable( bool e )
{
	bEnable = e;

	for ( auto temp : Enabled )
		temp( e );
}