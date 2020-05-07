#pragma once

#include "Transform.h"
#include "PhysicsData.h"
#include "Ray.h"

class Physics
{
public:
	Physics() = default;
	~Physics();


	void Init();
	void Update(PhysicsData& phyData, Transform &goTransform);

	Ray& GetRay() { return ray; }

private:
	Ray ray;
};

