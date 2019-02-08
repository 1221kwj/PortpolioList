#include "stdafx.h"
#include "GameModel.h"

#include "../ModelComponents/ModelComponents.h"

GameModel::GameModel
(
	wstring matFolder,
	wstring matFile,
	wstring meshFolder,
	wstring meshFile
)
	: shader( NULL )
	, velocity( 0.0f, 0.0f, 0.0f )
{
	model = new Model();
	model->ReadMaterial( matFolder, matFile );
	model->ReadMesh( meshFolder, meshFile );
}
GameModel::~GameModel()
{

	SAFE_DELETE( shader );
	SAFE_DELETE( model );
}

void GameModel::SetVelocity( Vector3 & vec )
{
	velocity = vec;
}

void GameModel::GetVelocity( Vector3* vec )
{ 
	*vec = velocity;
}

void GameModel::Update()
{
	CalcPosition();

	XMFLOAT4X4 t;
	GetTransformed( &t );

	model->CopyGlobalBoneTo( boneTransforms, t );
}

void GameModel::Render()
{
}

void GameModel::SetShader( wstring shaderName )
{
	ModelMaterials* m = model->GetComponent<ModelMaterials>( L"Material" );

	for ( Material* material : m->Materials() )
		material->SetShader( shaderName );
}

void GameModel::SetDiffuse( float r, float g, float b, float a )
{
	SetDiffuse( Vector4( r, g, b, a ) );
}

void GameModel::SetDiffuse( Vector4 & color )
{
	ModelMaterials* m = model->GetComponent<ModelMaterials>( L"Material" );

	for ( Material* material : m->Materials() )
		material->SetDiffuse( color );
}

void GameModel::SetDiffuseMap( wstring file )
{
	ModelMaterials* m = model->GetComponent<ModelMaterials>( L"Material" );

	for ( Material* material : m->Materials() )
		material->SetDiffuseMap( file );
}

void GameModel::SetSpecular( float r, float g, float b, float a )
{
	SetSpecular( Vector4( r, g, b, a ) );
}

void GameModel::SetSpecular( Vector4 & color )
{
	ModelMaterials* m = model->GetComponent<ModelMaterials>( L"Material" );

	for ( Material* material : m->Materials() )
		material->SetSpecular( color );
}

void GameModel::SetSpecularMap( wstring file )
{
	ModelMaterials* m = model->GetComponent<ModelMaterials>( L"Material" );

	for ( Material* material : m->Materials() )
		material->SetSpecularMap( file );
}

void GameModel::SetNormalMap( wstring file )
{
	ModelMaterials* m = model->GetComponent<ModelMaterials>( L"Material" );

	for ( Material* material : m->Materials() )
		material->SetNormalMap( file );
}

void GameModel::SetShininess( float val )
{
	ModelMaterials* m = model->GetComponent<ModelMaterials>( L"Material" );

	for ( Material* material : m->Materials() )
		material->SetShininess( val );
}

void GameModel::CalcPosition()
{
	XMVECTOR vel = XMLoadFloat3( &velocity );

	if ( XMVectorGetX( XMVector3Length( vel ) ) <= 0.0f ) return;
	
	XMVECTOR	vec		= XMVectorZero();
	Vector3		dir		= Vector3::Zero();
	Vector3		up		= Vector3::Zero();
	Vector3		right	= Vector3::Zero();
	
	GetDirection( &dir );
	GetRight	( &right );
	GetUp		( &up );
	
	if ( velocity.z != 0.0f ) vec += XMLoadFloat3( &dir )	* velocity.z;
	if ( velocity.y != 0.0f ) vec += XMLoadFloat3( &up )	* velocity.y;
	if ( velocity.x != 0.0f ) vec += XMLoadFloat3( &right ) * velocity.x;

	Vector3 pos = Vector3::Zero();
	GetPosition( &pos );

	XMVECTOR temp = XMVectorAdd( XMLoadFloat3( &pos ), vec * Time::Delta() );
	
	XMStoreFloat3( &pos, temp );

	SetPosition( pos );
}
