#include "stdafx.h"
#include "Export.h"

#include "../005_FbxExporter/FbxExporter.h"

Export::Export()
{
	Fbx::FbxExporter* exporter = NULL;

	//Plane
	//exporter = new Fbx::FbxExporter	( FbxFilePath + L"000_Figure/Plane.fbx" );
	//exporter->ExportMaterial		( BinaryFile + L"000_Figure/Plane/", L"Plane.material" );
	//exporter->ExportMesh			( BinaryFile + L"000_Figure/Plane/", L"Plane.mesh" );

	//Kachujin Mesh
	exporter = new Fbx::FbxExporter	( FbxCharPath		+ L"Kachujin/Kachujin.fbx" );
	exporter->ExportMaterial		( BinaryCharacter	+ L"Kachujin/", L"Kachujin.material" );
	exporter->ExportMesh			( BinaryCharacter	+ L"Kachujin/", L"Kachujin.mesh" );

	////Capsule
	//exporter = new Fbx::Exporter(Assets + L"Meshes/Capsule.fbx");
	//exporter->ExportMaterial(Materials + L"/Meshes/", L"Capsule.material");
	//exporter->ExportMesh(Models + L"/Meshes/", L"Capsule.mesh");
	//SAFE_DELETE(exporter);

	////Cube
	//exporter = new Fbx::Exporter(Assets + L"Meshes/Cube.fbx");
	//exporter->ExportMaterial(Materials + L"/Meshes/", L"Cube.material");
	//exporter->ExportMesh(Models + L"/Meshes/", L"Cube.mesh");
	//SAFE_DELETE(exporter);

	////Cylinder
	//exporter = new Fbx::Exporter(Assets + L"Meshes/Cylinder.fbx");
	//exporter->ExportMaterial(Materials + L"/Meshes/", L"Cylinder.material");
	//exporter->ExportMesh(Models + L"/Meshes/", L"Cylinder.mesh");
	//SAFE_DELETE(exporter);
	
	////Quad
	//exporter = new Fbx::Exporter(Assets + L"Meshes/Quad.fbx");
	//exporter->ExportMaterial(Materials + L"/Meshes/", L"Quad.material");
	//exporter->ExportMesh(Models + L"/Meshes/", L"Quad.mesh");
	//SAFE_DELETE(exporter);

	////Sphere
	//exporter = new Fbx::Exporter(Assets + L"Meshes/Sphere.fbx");
	//exporter->ExportMaterial(Materials + L"/Meshes/", L"Sphere.material");
	//exporter->ExportMesh(Models + L"/Meshes/", L"Sphere.mesh");
	//SAFE_DELETE(exporter);

	////Teapot
	//exporter = new Fbx::Exporter(Assets + L"Meshes/Teapot.fbx");
	//exporter->ExportMaterial(Materials + L"/Meshes/", L"Teapot.material");
	//exporter->ExportMesh(Models + L"/Meshes/", L"Teapot.mesh");
	//SAFE_DELETE(exporter);

	
	//SAFE_DELETE( exporter );

	//Tank Mesh
	//exporter = new Fbx::FbxExporter	( FbxFilePath	+ L"001_Character/Tank/Tank.fbx" );
	//exporter->ExportMaterial		( BinaryFile	+ L"001_Character/Tank/", L"Tank.material" );
	//exporter->ExportMesh			( BinaryFile	+ L"001_Character/Tank/", L"Tank.mesh" );
	//SAFE_DELETE( exporter );

	////Samba_Dancing
	//exporter = new Fbx::Exporter(Assets + L"Kachujin/Samba_Dancing.fbx");
	//exporter->ExportAnimation(Models + L"Kachujin/", L"Samba_Dance.anim", 0);
	//SAFE_DELETE(exporter);

	////Taunt
	//exporter = new Fbx::Exporter(Assets + L"Kachujin/Taunt.fbx");
	//exporter->ExportAnimation(Models + L"Kachujin/", L"Taunt.anim", 0);
	//SAFE_DELETE(exporter);

	////Running
	//exporter = new Fbx::Exporter(Assets + L"Kachujin/Running.fbx");
	//exporter->ExportAnimation(Models + L"Kachujin/", L"Running.anim", 0);
	//SAFE_DELETE(exporter);

	SAFE_DELETE( exporter );
}