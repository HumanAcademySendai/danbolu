#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"

class GameMain : public CGameScene {
public:
	GameMain() : DefaultFont(GraphicsDevice.CreateDefaultFont())
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~GameMain()
	{
#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();

		Finalize();
	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;

private:
	// ïœêîêÈåæ
	KeyboardState key;
	KeyboardBuffer key_buf;

	ANIMATIONMODEL player1;
	MODEL player2;
	MODEL player3;
	ANIMATIONMODEL player4;

	MODEL hitbox;
	MODEL hitbox2;
	MODEL hitbox3;
	MODEL hitbox4;

	bool test;


	float player_speed1;
	float player_speed4;

	MODEL map;
	Material material;

	CAMERA camera;
	Viewport viewport;
	
	CAMERA camera2;
	Viewport viewport2;

	// ä÷êîêÈåæ
	void Player_Initialize();
	void Player_Update();
	void Player_Draw();
	void Camera_Initialize();
	void Camera_Update();
	void Camera_Draw_1();
	void Camera_Draw_2();
};
