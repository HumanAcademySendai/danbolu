// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));

	/**
 * @brief ライトの初期設定
 */
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, 1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	Camera_Initialize();

	/**
* @brief マップの初期設定
*/
	map = GraphicsDevice.CreateModelFromFile(_T("map.X"));
	map->SetScale(0.1f);
	map->SetPosition(0, 0, 0);
	/**
* @brief マップのマテリアルの初期設定
*/
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 0.5f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power = 0.0f;
	map->SetMaterial(material);

	Player_Initialize();

	SimpleShape shape;
	shape.Type = Shape_Box;
	shape.Depth = 3;
	shape.Height = 10;
	shape.Width = 3;

	hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	hitbox->SetPosition(player1->GetPosition());
	hitbox->SetMaterial(material);

	SimpleShape shape2;
	shape2.Type = Shape_Box;
	shape2.Depth = 3;
	shape2.Height = 10;
	shape2.Width = 3;

	hitbox2 = GraphicsDevice.CreateModelFromSimpleShape(shape2);
	hitbox2->SetPosition(player2->GetPosition());
	hitbox2->SetMaterial(material);

	SimpleShape shape3;
	shape3.Type = Shape_Box;
	shape3.Depth = 3;
	shape3.Height = 10;
	shape3.Width = 3;

	hitbox3 = GraphicsDevice.CreateModelFromSimpleShape(shape3);
	hitbox3->SetPosition(player3->GetPosition());
	hitbox3->SetMaterial(material);

	SimpleShape shape4;
	shape4.Type = Shape_Box;
	shape4.Depth = 3;
	shape4.Height = 10;
	shape4.Width = 3;

	hitbox4 = GraphicsDevice.CreateModelFromSimpleShape(shape4);
	hitbox4->SetPosition(player4->GetPosition());
	hitbox4->SetMaterial(material);

	test = false;

	return true;


}
void GameMain::Player_Initialize()
{
	player1 = GraphicsDevice.CreateAnimationModelFromFile(_T("human_animetion22.X"));
	player1->SetScale(0.03);
	player1->SetPosition(0, 0, 0);
	player1->SetRotation(0, 0, 0);
	player_speed1 = 0.5;
	player1->SetTrackEnable(0, TRUE);

	player2 = GraphicsDevice.CreateModelFromFile(_T("dan_motion_Bodyblow_short_1p.X"));
	player2->SetScale(0.05);
	player2->SetPosition(10, 0, -10);
	player2->SetRotation(0, 0, 0);

	player3 = GraphicsDevice.CreateModelFromFile(_T("dan_motion_Bodyblow_short_1p.X"));
	player3->SetScale(0.05);
	player3->SetPosition(-10, 0, 10);
	player3->SetRotation(0, 0, 0);

	player4 = GraphicsDevice.CreateAnimationModelFromFile(_T("human_animetion22.X"));
	player4->SetScale(0.03);
	player4->SetPosition(-10, 0, -10);
	player4->SetRotation(0, 0, 0);
	player_speed4 = 0.5;
	player4->SetTrackEnable(0, TRUE);
}
void GameMain::Camera_Initialize()
{
	/**
* @brief カメラの初期設定
*/
	viewport = GraphicsDevice.GetViewport();
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = 640;
	viewport.Height = 720;
	camera->SetView(Vector3(0, 40, -40), Vector3(60, 0, 0));
	camera->SetPerspectiveFieldOfView(60.0f, viewport.Width, viewport.Height, 1.0f, 10000.0f);

	/**
* @brief カメラ2の初期設定
*/
	viewport2 = viewport;
	viewport2.X = viewport.Width;
	viewport2.Y = 0;
	viewport2.Width = 1280 - viewport.Width;
	viewport2.Height = 720;
	camera2->SetView(Vector3(0, 40, -40), Vector3(60, 0, 0));
	camera2->SetPerspectiveFieldOfView(60.0f, viewport2.Width, viewport2.Height, 1.0f, 10000.0f);

}
void GameMain::Finalize()
{
}

int GameMain::Update()
{

	/**
 * @brief　キーボードの設定
 */
	key = Keyboard->GetState();
	key_buf = Keyboard->GetBuffer();

	Player_Update();
	Camera_Update();

	hitbox->SetPosition(player1->GetPosition());
	hitbox->SetDirection(player1->GetDirectionQuaternion());

	hitbox2->SetPosition(player2->GetPosition());
	hitbox2->SetDirection(player2->GetDirectionQuaternion());

	hitbox3->SetPosition(player3->GetPosition());
	hitbox3->SetDirection(player3->GetDirectionQuaternion());

	hitbox4->SetPosition(player4->GetPosition());
	hitbox4->SetDirection(player4->GetDirectionQuaternion());

	OrientedBoundingBox player1_hitbox = hitbox->GetOBB();
	OrientedBoundingBox player2_hitbox = hitbox2->GetOBB();
	OrientedBoundingBox player3_hitbox = hitbox3->GetOBB();
	OrientedBoundingBox player4_hitbox = hitbox4->GetOBB();

	if (player1_hitbox.Intersects(player2_hitbox)&&key_buf.IsPressed(Keys_K))
	{
		player2->SetRotation(0, 0, 90);
	}

	return 0;
}

void GameMain::Player_Update()
{
	/**
* @brief　プレイヤー１の移動
*/
	if (key.IsKeyDown(Keys_D))
	{
		player1->Rotation(0, 2, 0);
	}
	if (key.IsKeyDown(Keys_A))
	{
		player1->Rotation(0, -2, 0);
	}
	if (key.IsKeyDown(Keys_W))
	{
		player1->Move(0, 0, -player_speed1);
	}
	if (key.IsKeyDown(Keys_S))
	{
		player1->Move(0, 0, player_speed1);
	}
	/**
* @brief　プレイヤー４の移動
*/
	if (key.IsKeyDown(Keys_Right))
	{
		player4->Rotation(0, 2, 0);
	}
	if (key.IsKeyDown(Keys_Left))
	{
		player4->Rotation(0, -2, 0);
	}
	if (key.IsKeyDown(Keys_Up))
	{
		player4->Move(0, 0, -player_speed4);
	}
	if (key.IsKeyDown(Keys_Down))
	{
		player4->Move(0, 0, player_speed4);
	}
}
void GameMain::Camera_Update()
{
	/**
* @brief　プレイヤー１とプレイヤー２の中央と距離を測る
*/
	float center_x = (player1->GetPosition().x + player2->GetPosition().x) / 2;
	float center_z = (player1->GetPosition().z + player2->GetPosition().z) / 2;
	float distance_1 = Vector3_Distance(player1->GetPosition(), player2->GetPosition());
	/**
* @brief　プレイヤー３とプレイヤー４の中央と距離を測る
*/
	float center_x_2 = (player3->GetPosition().x + player4->GetPosition().x) / 2;
	float center_z_2 = (player3->GetPosition().z + player4->GetPosition().z) / 2;
	float distance_2 = Vector3_Distance(player3->GetPosition(), player4->GetPosition());
	/**
* @brief　カメラの場所
*/
	camera2->SetPosition(center_x, 30 + distance_1, center_z - 20);
	camera->SetPosition(center_x_2, 30 + distance_2, center_z_2 - 20);
}
void GameMain::Draw()
{

	GraphicsDevice.BeginScene();

	Camera_Draw_1();

	Camera_Draw_2();

	GraphicsDevice.EndScene();
}
void GameMain::Player_Draw()
{
	player1->AdvanceTime(GameTimer.GetElapsedSecond());
	player1->Draw();
	player2->Draw();
	if (test == true)
	{
		player3->Draw();
	}
	player4->AdvanceTime(GameTimer.GetElapsedSecond());
	player4->Draw();
	//player3->Draw();
}
void GameMain::Camera_Draw_1()
{
	GraphicsDevice.SetCamera(camera);
	GraphicsDevice.SetViewport(viewport);
	GraphicsDevice.Clear(Color_CornflowerBlue);

	map->Draw();
	Player_Draw();
	hitbox->Draw();
	hitbox2->Draw();
	hitbox3->Draw();
	hitbox4->Draw();
}
void GameMain::Camera_Draw_2()
{
	GraphicsDevice.SetCamera(camera2);
	GraphicsDevice.SetViewport(viewport2);
	GraphicsDevice.Clear(Color_CornflowerBlue);

	map->Draw();
	Player_Draw();
	hitbox->Draw();
	hitbox2->Draw();
	hitbox3->Draw();
	hitbox4->Draw();
}
