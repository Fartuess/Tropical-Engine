#pragma once

#include "Animations_header.h"
#include "Simulations_header.h"
#include "Scene_header.h"
#include "ModelGeneration_header.h"

	
	float zeroTab[3] = {0.0f, 0.0f, 0.0f};
	float oneTab[3] = {1.0f, 1.0f, 1.0f};
	GameObject* scene;
	Door* Door1;
	Door* Door2;
	float time;

	//debug
	MaterialPoint* mPoint1;
	MaterialPoint* mPoint2;

void CreateScene()
{
	GameObject* tempGameObject;
	currentCamera= new Camera(new Vec3(0.0f, 31.0f, -22.0f), new Vec3(0.0f, 31.0f, -21.0f), new Vec3(0.0f, 1.0f, 0.0f));

	TextureManager::Load("default", new Texture("GenericTiles.tga"));
	TextureManager::Load("default_spec", new Texture("GenericTiles_Spec.tga"));
	TextureManager::Load("default_n", new Texture("GenericTiles_NRM.tga"));
	TextureManager::Load("normal", new Texture("normal.tga"));

	TextureManager::Load("desk_diff", new Texture("Desk_Diff.tga"));
	TextureManager::Load("desk_spec", new Texture("Desk_Spec.tga"));
	TextureManager::Load("desk_n", new Texture("Desk_normals.tga"));
	TextureManager::Load("table_diff", new Texture("Table_Diff.tga"));
	TextureManager::Load("table_spec", new Texture("Table_Spec.tga"));
	TextureManager::Load("bar_diff", new Texture("Bar_Diff.tga"));
	TextureManager::Load("bar_spec", new Texture("Bar_Spec.tga"));
	TextureManager::Load("chair_diff", new Texture("Chair_Diff.tga"));
	TextureManager::Load("chair_spec", new Texture("Chair_Spec.tga"));
	TextureManager::Load("tiles_diff", new Texture("CeramicTiles_Diff.tga"));
	TextureManager::Load("tiles_spec", new Texture("CeramicTiles_Spec.tga"));
	TextureManager::Load("tiles_n", new Texture("CeramicTiles_normals.tga"));
	TextureManager::Load("door_diff", new Texture("Door_Diff.tga"));
	TextureManager::Load("door_spec", new Texture("Door_Spec.tga"));
	TextureManager::Load("sky_tex", new Texture("SkyTexture.tga"));
	TextureManager::Load("room_diff", new Texture("Room_Diff.tga"));
	TextureManager::Load("room_spec", new Texture("Room_Spec.tga"));
	TextureManager::Load("room_n", new Texture("Room_n.tga"));
	TextureManager::Load("bariercolumn_diff", new Texture("BalconyBarierColumn_Diff.tga"));
	TextureManager::Load("bariercolumn_spec", new Texture("BalconyBarierColumn_Spec.tga"));
	TextureManager::Load("barier_diff", new Texture("BalconyBarrier_Diff.tga"));
	TextureManager::Load("barier_spec", new Texture("BalconyBarrier_Spec.tga"));
	TextureManager::Load("ceramicpot_diff", new Texture("CeramicPot_Diff.tga"));
	TextureManager::Load("ceramicpot_spec", new Texture("CeramicPot_Spec.tga"));
	TextureManager::Load("ceramicpot_n", new Texture("CeramicPot_normals.tga"));
	TextureManager::Load("dirt_diff", new Texture("Dirt_Diff.tga"));
	TextureManager::Load("dirt_spec", new Texture("Dirt_Spec.tga"));

	ModelManager::Load("desk", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(0.65f, 0.65f, 0.65f), "Desk.obj", "desk_diff", "desk_spec", "desk_n"));
	ModelManager::Load("chair", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(0.2f, 0.2f, 0.2f), "Chair.obj", "chair_diff" ,"chair_spec"));
	ModelManager::Load("table", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(0.7f, 0.7f, 0.7f), "Table.obj", "table_diff" ,"table_spec"));
	ModelManager::Load("bar", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(3.0f, 3.0f, 3.0f), "Bar.obj", "bar_diff" ,"bar_spec"));
	ModelManager::Load("armchair", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(3.5f, 3.5f, 3.5f), "Armchair.obj"));
	ModelManager::Load("balcony", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(19.2f, 19.2f, 19.2f), "BalconyFloor.obj", "tiles_diff" ,"tiles_spec", "tiles_n"));
	ModelManager::Load("balconybarier", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(19.2f, 19.2f, 19.2f), "BalconyBarier.obj", "barier_diff" ,"barier_spec"));
	ModelManager::Load("windowframe", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.24f, 1.28f, 1.28f), "WindowFrame.obj"));
	ModelManager::Load("window", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.24f, 1.28f, 1.28f), "Window.obj"));
	ModelManager::Load("balconydoorframe", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.24f, 1.28f, 1.28f), "BalconyDoorFrame.obj"));
	ModelManager::Load("balconydoor", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.24f, 1.28f, 1.28f), "BalconyDoor.obj"));
	ModelManager::Load("ceramicpot", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(2.0f, 2.0f, 2.0f), "CeramicPot.obj", "ceramicpot_diff" ,"ceramicpot_spec", "ceramicpot_n"));
	ModelManager::Load("disc", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(2.0f, 2.0f, 2.0f), "Disc.obj", "dirt_diff" ,"dirt_spec"));
	ModelManager::Load("barier", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.5f, 1.5f, 1.5f), "BalconyBarierColumn.obj", "bariercolumn_diff" ,"bariercolumn_spec"));
	ModelManager::Load("room", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.1f, 0.1f, 0.1f), "Room.obj", "room_diff", "room_spec", "room_n"));
	ModelManager::Load("door", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.5f, 0.5f, 0.5f), "Door.obj", "door_diff", "door_spec"));
	ModelManager::Load("sky", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(50.0f, 50.0f, 50.0f), "SkyDome.obj", "sky_tex"));
	ModelManager::Load("fireplace", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(6.0f, 6.0f, 6.0f), "Fireplace.obj"));
	ModelManager::Load("smallpalm", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.25f, 1.25f, 1.25f), "SmallPalm.obj"));
	ModelManager::Load("physiccube", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(2.00f, 2.00f, 2.00f), "PhysicCube.obj"));
	ModelManager::Load("physicwall", new Model(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.00f, 1.00f, 1.00f), "PhysicWall.obj"));

	scene = new GameObject(new Vec3(0.0f, 10.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f));
	
	scene->AddSubObject(new GameObject(new Vec3(-12.0f, 12.8f, -4.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("desk")->second));
	scene->AddSubObject(new GameObject(new Vec3(-8.8f, 12.8f, -4.8f ), new Vec3(0.0f, 180.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("chair")->second));
	scene->AddSubObject(new GameObject(new Vec3(0.8f, 12.8f,-8.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("table")->second));
	scene->AddSubObject(new GameObject(new Vec3(-1.6f, 12.8f,-27.2f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("bar")->second));
	scene->AddSubObject(new GameObject(new Vec3(11.2f, 14.2f,-3.2f), new Vec3(0.0f, -200.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("armchair")->second));
	scene->AddSubObject(new GameObject(new Vec3(10.4f, 11.6f, 12.8f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("balcony")->second));
	scene->AddSubObject(new GameObject(new Vec3(10.4f, 16.6f, 12.7f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("balconybarier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-6.0f, 12.8f, 12.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("windowframe")->second));
	scene->AddSubObject(new GameObject(new Vec3(-6.0f, 12.8f, 12.0f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("window")->second));
	scene->AddSubObject(new GameObject(new Vec3(-11.6f, 12.8f, 12.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("windowframe")->second));
	scene->AddSubObject(new GameObject(new Vec3(-11.6f, 12.8f, 12.0f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("window")->second));
	scene->AddSubObject(new GameObject(new Vec3(9.6f, 12.8f, 12.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("windowframe")->second));
	scene->AddSubObject(new GameObject(new Vec3(9.6f, 12.8f, 12.0f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("window")->second));
	scene->AddSubObject(new GameObject(new Vec3(15.2f, 12.8f, 12.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("windowframe")->second));
	scene->AddSubObject(new GameObject(new Vec3(15.2f, 12.8f, 12.0f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("window")->second));
	scene->AddSubObject(new GameObject(new Vec3(-0.4f, 12.8f, 12.0f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("balconydoorframe")->second));
	scene->AddSubObject(new GameObject(new Vec3(4.0f, 12.8f, 12.0f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("balconydoorframe")->second));
	//Balcony Doors
	Door1 = new Door(new Vec3(-2.6f, 12.8f, 12.4f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("balconydoor")->second, 152.0f, false);
	Door2 = new Door(new Vec3(6.2f, 12.8f, 12.4f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("balconydoor")->second, -152.0f, false);
	
	scene->AddSubObject(Door1);
	scene->AddSubObject(Door2);
	tempGameObject = new GameObject(new Vec3(-10.4f, 12.4f, 23.2f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("ceramicpot")->second);
	scene->AddSubObject(tempGameObject);
	tempGameObject->AddSubObject(new GameObject(new Vec3(0.0f, 3.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("disc")->second));
	tempGameObject->AddSubObject(new GameObject(new Vec3(0.0f, 3.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("smallpalm")->second));
	//Balcony barriers
	scene->AddSubObject(new GameObject(new Vec3(-9.2f, 12.8f, 30.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-6.0f, 12.8f, 30.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-2.8f, 12.8f, 30.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(0.4f, 12.8f, 30.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(3.6f, 12.8f, 30.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(6.8f, 12.8f, 30.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(10.0f, 12.8f, 30.8f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	//Left Side
	scene->AddSubObject(new GameObject(new Vec3(13.2f, 12.8f, 30.4f), new Vec3(0.0f, 11.25f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(16.3f, 12.8f, 29.75f), new Vec3(0.0f, 16.75f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(19.15f, 12.8f, 28.35f), new Vec3(0.0f, 28.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(21.8f, 12.8f, 26.75f), new Vec3(0.0f, 33.75f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(24.15f, 12.8f, 24.38f), new Vec3(0.0f, 50.5f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(26.0f, 12.8f, 21.7f), new Vec3(0.0f, 62.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(27.2f, 12.8f, 18.8f), new Vec3(0.0f, 67.5f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(28.2f, 12.8f, 15.7f), new Vec3(0.0f, 78.75f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	//Right Side
	scene->AddSubObject(new GameObject(new Vec3(-11.4f, 12.8f, 30.4f), new Vec3(0.0f, -11.25f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-14.5f, 12.8f, 29.75f), new Vec3(0.0f, -16.75f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-17.35f, 12.8f, 28.35f), new Vec3(0.0f, -28.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-20.2f, 12.8f, 26.75f), new Vec3(0.0f, -33.75f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-22.55f, 12.8f, 24.38f), new Vec3(0.0f, -50.5f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-24.4f, 12.8f, 21.7f), new Vec3(0.0f, -62.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-25.6f, 12.8f, 18.8f), new Vec3(0.0f, -67.5f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	scene->AddSubObject(new GameObject(new Vec3(-26.6f, 12.8f, 15.7f), new Vec3(0.0f, -78.75f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("barier")->second));
	//Barriers end
	scene->AddSubObject(new GameObject(new Vec3(1.8f, 12.8f, -8.2f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("room")->second));
	scene->AddSubObject(new GameObject(new Vec3(8.9f, 17.8f, -31.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("door")->second));
	scene->AddSubObject(new GameObject(new Vec3(9.0f, 17.8f, -31.0f), new Vec3(0.0f, 180.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("door")->second));
	scene->AddSubObject(new GameObject(new Vec3(-15.8f, 17.8f, 3.8f), new Vec3(0.0f, 90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("door")->second));
	scene->AddSubObject(new GameObject(new Vec3(0.0f, -20.0f, 0.0f), new Vec3(0.0f, -40.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("sky")->second));
	scene->AddSubObject(new GameObject(new Vec3(18.0f, 12.8f, -10.8f), new Vec3(0.0f, -90.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("fireplace")->second));
	//Animation testing
	
	Keyframe* keyframe1 = new Keyframe(new Vec3(0.0f, 0.0f, 0.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(8.0f, 0.0f, 0.0f));
	Keyframe* keyframe2 = new Keyframe(new Vec3(0.0f, 4.0f, 0.0f), new Vec3(8.0f, 4.0f, 0.0f), new Vec3(-4.0f, 4.0f, 0.0f));
	Keyframe* keyframe3 = new Keyframe(new Vec3(10.0f, 0.0f, 0.0f), new Vec3(10.0f, -8.0f, 0.0f), new Vec3(10.0f, 0.0f, 0.0f));
	
	Animation* animation1 = new Animation();
		animation1->AddKeyframe(0, keyframe1);
		animation1->AddKeyframe(2, keyframe2);
		animation1->AddKeyframe(4, keyframe3);
		animation1->AddKeyframe(6, keyframe1);
	
	scene->AddSubObject(new GameObject(&animation1->value, new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("physiccube")->second));
	
	animation1->StartAnimation(true, true, 2.0f);
	//Physics testing
	mPoint1 = new MaterialPoint(Vec3(0.0f, 20.0f, 0.0f), 1.0f);
	mPoint2 = new MaterialPoint(Vec3(0.0f, 20.0f, -200.0f), 1.0f);//static Material Point for wall
	//Collider* PhysicBoxCollider = new AABBCollider(Vec3(-1.0f,-1.0f,-1.0f), Vec3(1.0f,1.0f,1.0f));
	scene->AddSubObject(new GameObject(new Vec3(80.0f, 10000.0f, 20.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("physiccube")->second, mPoint1));//, new AABBCollider(Vec3(-1.0f,-1.0f,-1.0f), Vec3(1.0f,1.0f,1.0f))));
	//scene->AddSubObject(new GameObject(new Vec3(80.0f, 10000.0f, 20.0f), new Vec3(0.0f, 0.0f, 0.0f), new Vec3(1.0f, 1.0f, 1.0f), false, ModelManager::models.find("physicwall")->second, mPoint2));
	
	//Shader* phong = new Shader

	//Model generationTest
	ModelManager::Load("proceduralPlane", new Model(&Vec3Zero, &Vec3Zero, &Vec3One, ModelGenerator::generatePlane(1.0f, 1.0f, 3,  3)));
	scene->AddSubObject(new GameObject(new Vec3(-10.0f, 0.0f, 0.0f), &Vec3Zero, new Vec3(5.0f, 5.0f, 5.0f), false, ModelManager::models.find("proceduralPlane")->second));
	//ModelManager::Load("proceduralTriangle", new Model(&Vec3Zero, &Vec3Zero, &Vec3One, ModelGenerator::generateTriangle()));
	//scene->AddSubObject(new GameObject(new Vec3(0.0f, 0.0f, 0.0f), &Vec3Zero, new Vec3(100.0f, 100.0f, 100.0f), false, ModelManager::models.find("proceduralTriangle")->second));
	ModelManager::Load("proceduralCube", new Model(&Vec3Zero, &Vec3Zero, &Vec3One, ModelGenerator::generateCube(1.0f, 1.0f, 1.0f, 3, 3, 3)));
	scene->AddSubObject(new GameObject(new Vec3(10.0f, 0.0f, 0.0f), &Vec3Zero, new Vec3(5.0f, 5.0f, 5.0f), false, ModelManager::models.find("proceduralCube")->second));
	ModelManager::Load("proceduralCylinder", new Model(&Vec3Zero, &Vec3Zero, &Vec3One, ModelGenerator::generateCylinder(1.0f, 1.0f, 50, 3)));
	scene->AddSubObject(new GameObject(new Vec3(0.0f, 0.0f, -10.0f), &Vec3Zero, new Vec3(5.0f, 5.0f, 5.0f), false, ModelManager::models.find("proceduralCylinder")->second));
	ModelManager::Load("proceduralCone", new Model(&Vec3Zero, &Vec3Zero, &Vec3One, ModelGenerator::generateCone(1.0f, 1.0f, 50, 3)));
	scene->AddSubObject(new GameObject(new Vec3(-10.0f, 0.0f, -10.0f), &Vec3Zero, new Vec3(5.0f, 5.0f, 5.0f), false, ModelManager::models.find("proceduralCone")->second));
	ModelManager::Load("proceduralSphere", new Model(&Vec3Zero, &Vec3Zero, &Vec3One, ModelGenerator::generateSphere(1.0f, 20, 20)));
	scene->AddSubObject(new GameObject(new Vec3(0.0f, 0.0f, 0.0f), &Vec3Zero, new Vec3(5.0f, 5.0f, 5.0f), false, ModelManager::models.find("proceduralSphere")->second));
}