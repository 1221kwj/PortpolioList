#include "stdafx.h"
#include "Freedom.h"

Freedom::Freedom( float moveSpeed, float rotationSpeed )
	: moveSpeed		( moveSpeed )
	, rotationSpeed	( rotationSpeed )
{
}

Freedom::~Freedom()
{
}

void Freedom::Update()
{
	Vector3 forward = Vector3::Zero();
	Vector3 right	= Vector3::Zero();
	Vector3 up		= Vector3::Zero();

	GetForward	( &forward );
	GetRight	( &right );
	GetUp		( &up );

	//捞悼贸府
	{
		Vector3 pos = Vector3::Zero();
		GetPosition( &pos );

		if ( Mouse::Get()->Press( 1 ) )
		{
			if ( Keyboard::Get()->Press( 'W' ) )
				pos += forward * moveSpeed * Time::Delta();
			else if ( Keyboard::Get()->Press( 'S' ) )
				pos += -forward * moveSpeed * Time::Delta();

			if ( Keyboard::Get()->Press( 'A' ) )
				pos += -right * moveSpeed * Time::Delta();
			else if ( Keyboard::Get()->Press( 'D' ) )
				pos += right * moveSpeed * Time::Delta();

			if ( Keyboard::Get()->Press( 'E' ) )
				pos += up * moveSpeed * Time::Delta();
			else if ( Keyboard::Get()->Press( 'Q' ) )
				pos += -up * moveSpeed * Time::Delta();

			SetPosition( pos.x, pos.y, pos.z );
		}
	}

	//雀傈贸府
	{
		Vector2 rot = Vector2::Zero();
		GetRotation( &rot );

		if ( Mouse::Get()->Press( 1 ) )
		{
			Vector3 val = Vector3::Zero();
			Mouse::Get()->GetMoveValue( &val );
			rot.x += val.y * rotationSpeed * Time::Delta();
			rot.y += val.x * rotationSpeed * Time::Delta();
		}

		SetRotation( rot.x, rot.y );
	}
}
