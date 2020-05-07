#include "Player.h"
#include "Locator.h"
#include "Timer.h"
#include "WinSetup.h"
#include "Keyboard.h"
#include "imgui/imgui.h"

#include <iostream>

using namespace DirectX;

Player::~Player()
{
	stateMap[ObjectMotionState::FALLING] = "falling";
	stateMap[ObjectMotionState::GROUNDED] = "ground";
}

void Player::Init()
{
	mVelocity = XMVectorZero();
}

void Player::Update(PhysicsData& physData, Transform& goTransform)
{

	auto dt = Locator::GetTimer()->DeltaTime();
	Vec4 vecForward{0.0f, VectorY(mVelocity), 0.0f, 1.0f};
	Vec4 vecRight{0.0f, VectorY(mVelocity), 0.0f, 1.0f};
	if (Locator::GetKey()->IsKeyPressed('D') || Locator::GetKey()->IsKeyRepeated('D'))
	{
		physData.m_Force.x = 25;
		goTransform.SetRotY(90);
	}
	else if (Locator::GetKey()->IsKeyPressed('A') || Locator::GetKey()->IsKeyRepeated('A'))
	{
		physData.m_Force.x = -25;
		goTransform.SetRotY(270);
	}
	if (Locator::GetKey()->IsKeyPressed(VK_SPACE))
	{
		physData.m_Force.y = 100;
		physData.motionState = ObjectMotionState::FALLING;
	}


	//if ((Locator::GetKey()->IsKeyReleased('D') && !(Locator::GetKey()->IsKeyPressed('A') || Locator::GetKey()->IsKeyRepeated('A')))
	//	|| (Locator::GetKey()->IsKeyReleased('A') && !(Locator::GetKey()->IsKeyPressed('D') || Locator::GetKey()->IsKeyRepeated('D'))))
	//{
	//	physData.m_ForceDir.x = 0;
	//	physData.m_Force.x = 0;
	//}


	//if (Locator::GetKey()->IsKeyPressed('W') || Locator::GetKey()->IsKeyRepeated('W'))
	//{
	//	vecForward = { 0, 0, -1};
	//	goTransform.SetRotY(0);
	//}
	//else if (Locator::GetKey()->IsKeyPressed('S') || Locator::GetKey()->IsKeyRepeated('S'))
	//{
	//	vecForward = { 0, 0, 1};
	//	goTransform.SetRotY(180);
	//}

	//auto vel = vecForward + vecRight;
	//vel = DirectX::XMVector4Normalize(vel);
	//mVelocity = { VectorX(vel) * mSpeed, VectorY(mVelocity), VectorZ(vel) * mSpeed };

	//if (Locator::GetKey()->IsKeyPressed('Q') || Locator::GetKey()->IsKeyRepeated('Q'))
	//{
	//	goTransform.SetRotY(goTransform.GetRotY() - mRotSpeed * Locator::GetTimer()->DeltaTime());
	//}
	//else if (Locator::GetKey()->IsKeyPressed('E') || Locator::GetKey()->IsKeyRepeated('E'))
	//{
	//	goTransform.SetRotY(goTransform.GetRotY() + mRotSpeed * Locator::GetTimer()->DeltaTime());
	//}

	//if (Locator::GetKey()->IsKeyReleased('W') || Locator::GetKey()->IsKeyReleased('S'))
	//{
	//	Vec4 vec = { 0.0f, VectorY(mVelocity), 0.0f };
	//	mVelocity = vec;
	//}

	//switch (state)
	//{
	//case ObjectMotionState::GROUNDED:
	//{
	//	acceleration = 0.0f;
	//	mVelocity = VectorSetY(mVelocity, 0.0f);
	//	break;
	//}
	//case ObjectMotionState::FALLING:
	//{
	//	acceleration += (GRAVITY * mass);
	//	acceleration -= drag;
	//	mVelocity = VectorSetY(mVelocity, VectorY(mVelocity) - acceleration);
	//	break;
	//}
	//}
	//Vector4 vec3 = mVelocity * dt;
	//goTransform.SetPos(goTransform.GetPos() + vec3);

	//if (ImGui::Begin("Velocity"))
	//{
	//	ImGui::Text("State: %i", (int)state);
	//}
	//ImGui::End();

}

//ObjectMotionState Player::GetState()
//{
//	return state;
//}
//
//void Player::SetState(ObjectMotionState _state)
//{
//	state = _state;
//}

const Vec4& Player::GetVelocity()
{
	return mVelocity;
}
