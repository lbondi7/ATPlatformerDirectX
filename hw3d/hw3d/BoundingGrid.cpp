#include "BoundingGrid.h"
#include "Utilities.h"

BoundingGrid::~BoundingGrid()
{

	for (auto& o : m_Objects)
	{
		o = nullptr;
	}
	m_Objects.clear();
	m_Bounds.clear();
}

void BoundingGrid::Init(Float3 dimensions)
{
	m_VoxelDimensions = dimensions;
	Float3 start = m_Min;
	while (start.z <= m_Max.z)
	{
		while (start.y <= m_Max.y)
		{
			while (start.x <= m_Max.x)
			{
				Bounds b;
				b.m_Min = start;
				b.m_Max = Utilities::AddFloat(start, m_VoxelDimensions);
				m_Bounds.emplace_back(b);
				start.x += m_VoxelDimensions.x;
			}
			start.y += m_VoxelDimensions.y;
			start.x = m_Min.x;
		}
		start.z += m_VoxelDimensions.z;
		start.y = m_Min.y;
		start.x = m_Min.x;
	}

	int asd = 0;

}

void BoundingGrid::Init(Float3 dimensions, Float3 min, Float3 max)
{
	m_VoxelDimensions = dimensions;
	m_Min = min;
	m_Max = max;
	Float3 start = m_Min;
	while (start.z < m_Max.z)
	{
		while (start.y < m_Max.y)
		{
			while (start.x < m_Max.x)
			{
				Bounds b;
				b.m_Min = start;
				b.m_Max = Utilities::AddFloat(start, m_VoxelDimensions);
				m_Bounds.emplace_back(b);
				start.x += m_VoxelDimensions.x;
			}
			start.y += m_VoxelDimensions.y;
			start.x = m_Min.x;
		}
		start.z += m_VoxelDimensions.z;
		start.y = m_Min.y;
		start.x = m_Min.x;
	}
}

void BoundingGrid::GetObjectIDs(std::vector<GameObject*>& objects)
{
	m_Objects = objects;
	for (auto& o : m_Objects)
	{
		o->BoundIDs().clear();
		for (size_t j = 0; j < m_Bounds.size(); ++j)
		{
			if (o->GetBB().IsInside(m_Bounds[j]))
				o->BoundIDs().emplace_back(j);

		}
	}

}

void BoundingGrid::GetObjectsInGrid(GameObject* object, std::vector<GameObject*>& otherObjects)
{
	for (auto& o : m_Objects)
	{
		if (o == object)
			continue;

		for (auto& ooBID : o->BoundIDs())
		{
			for (auto& oBID : object->BoundIDs())
			{
				if (ooBID == oBID)
					otherObjects.emplace_back(o);
			}
		}

		//for (size_t j = 0; j < bounds.size(); ++j)
		//{
		//	if (objects[i]->GetBB().IsInside(bounds[j]))
		//		objects[i]->BoundIDs().emplace_back(j);

		//}
	}

}
