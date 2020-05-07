#pragma once

#include "Maths.h"
#include "Bounds.h"
#include "GameObject.h"


class BoundingGrid
{
public: 
	BoundingGrid() = default;
	~BoundingGrid();

	void Init(Float3 dimensions);
	void Init(Float3 dimensions, Float3 min, Float3 max);

	void GetObjectIDs(std::vector<GameObject*>& objects);

	void GetObjectsInGrid(GameObject* object, std::vector<GameObject*>& otherObjects);


private:

	Float3 m_Min{-100, -50, -50};
	Float3 m_Max{ 100, 50, 50 };
	Float3 m_VoxelDimensions;

	std::vector<Bounds> m_Bounds;
	std::vector<GameObject*> m_Objects;

};

