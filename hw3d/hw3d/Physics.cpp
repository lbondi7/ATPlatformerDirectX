#include "Physics.h"

#include <algorithm>


Physics::~Physics()
{
}

void Physics::Init()
{
}

void Physics::Update(PhysicsData& physData, Transform& goTransform)
{
	Float3 ori = Utilities::ConvertToFloat3(goTransform.GetPos());
	ori.y -= goTransform.GetScaleY();
	ray.Origin(ori);

	float drag = 0.0f;
	switch (physData.motionState)
	{
	case ObjectMotionState::FALLING:
	{
		physData.m_Force.y -= GRAVITY * FIXED_DT * FIXED_DT;
		drag = 1.0f;
		physData.m_Velocity.y += (physData.m_Force.y * FIXED_DT);
		//physData.m_Force.y -= drag;
		//auto weight = physData.m_Force.y * GRAVITY;
		////physData.m_Force.y = std::clamp(physData.m_Force.y, -100.5f, 100.0f);
		//physData.m_Acceleration.y = ((weight / physData.m_Mass));
		break;
	}
	case ObjectMotionState::GROUNDED:
	{
		physData.m_Force.y = 0.0f;
		physData.m_Acceleration.y = 0.0f;
		physData.m_Velocity.y = 0.0f;

		drag = 2.0f;
		float friction = 150.0f;
		////friction = physData.m_Force.x * ;
		if (physData.m_Force.x > 0.5f)
			physData.m_Force.x -= (friction * FIXED_DT);

		if (physData.m_Force.x < -0.5f)
			physData.m_Force.x += (friction * FIXED_DT);

		if (std::abs(physData.m_Force.x) < 0.5f)
			physData.m_Force.x = 0.0f;

		//physData.m_Acceleration.x = (physData.m_Force.x / physData.m_Mass);

		//if(physData.m_Acceleration.x > 100.0f)

		//const float friction = 7.0f;

		//if (physData.m_Acceleration.x > 0)
		//	physData.m_Acceleration.x -= FIXED_DT;
		//			   
		//if (physData.m_Acceleration.x < 0)
		//	physData.m_Acceleration.x += FIXED_DT;

		////if (physData.m_Force.x < 0.0001f && 
		////	physData.m_Force.x > -0.0001f)
		////	physData.m_Force.x = 0.0f;

		//physData.m_Acceleration.x = std::clamp(physData.m_Acceleration.x, -20.0f, 20.5f);

		//if (physData.m_Velocity.x > 0.0f)
		//	physData.m_Velocity.x -= FIXED_DT;

		//if (physData.m_Velocity.x < 0.0f)
		//	physData.m_Velocity.x += FIXED_DT;

		//if (physData.m_Velocity.x < 0.0001f && 
		//	physData.m_Velocity.x > -0.0001f)
		//	physData.m_Velocity.x = 0.0f;


		break;
	}
	}

	physData.m_Velocity.x = physData.m_Force.x * FIXED_DT;
	//physData.m_Velocity.x += physData.m_Acceleration.x * FIXED_DT;
	//physData.m_Velocity.y += physData.m_Acceleration.y * FIXED_DT;

	auto stest = Utilities::ConvertToVec4Point(physData.m_Velocity);
	stest = VecAdd(goTransform.position, stest);
	goTransform.position = stest;
}
