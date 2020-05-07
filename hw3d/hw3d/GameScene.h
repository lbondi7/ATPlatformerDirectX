#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "BoundingGrid.h"

#include <memory>
#include <vector>

class GameScene :
	public Scene
{
public:
	~GameScene() override;

	bool Init() override;
	Scene::CurrentScene Update() override;
	void Render() override;

private:
	enum class ChangeScene : int
	{
		NONE = 0,
		MENU = 1
	};

	ChangeScene changeScene = ChangeScene::NONE;

	int mObjNum = 0;

	std::unique_ptr<Camera> mCam;
	std::vector<GameObject*> p_GObjects;
	std::unique_ptr<GameObject> pPlayer;
	Matrix mWorldMatrix = DirectX::XMMatrixIdentity();

	bool isColliding = false;

	LightBufferData light;
	std::unique_ptr<BoundingGrid> grid;
	std::vector<GameObject*> m_CollideableObjects;
};