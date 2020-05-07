#pragma once

class Scene
{
public:
	enum class CurrentScene : int
	{
		NONE = 0,
		MENU = 1,
		GAME = 2,
		LEVEL_EDITOR = 3,
	};

	Scene() = default;
	virtual ~Scene() = default;

	virtual bool Init() = 0;
	virtual CurrentScene Update() = 0;
	virtual void Render() = 0;

private:

};