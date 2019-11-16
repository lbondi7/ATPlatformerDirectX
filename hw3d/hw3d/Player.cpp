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
	stateMap[PlayerMotionState::FALLING] = "falling";
	stateMap[PlayerMotionState::GROUNDED] = "ground";
}

void Player::Init()
{
	mVelocity = XMVectorZero();
}

void Player::Update(Transform& goTransform)
{

	auto dt = Locator::GetTimer()->DeltaTime();
	Vector vecForward{0.0f, VectorY(mVelocity), 0.0f};
	Vector vecRight{0.0f, VectorY(mVelocity), 0.0f};
	if (Locator::GetKey()->IsKeyPressed('W') || Locator::GetKey()->IsKeyRepeated('W'))
	{
		vecForward = { 0, 0, mSpeed};
		vecForward = VectorTransform(vecForward, MatrixFromY(goTransform.GetRotYRad()));
	}
	else if (Locator::GetKey()->IsKeyPressed('S') || Locator::GetKey()->IsKeyRepeated('S'))
	{
		vecForward = { 0, 0, -mSpeed};
		vecForward = VectorTransform(vecForward, MatrixFromY(goTransform.GetRotYRad()));
	}
	if (Locator::GetKey()->IsKeyPressed('D') || Locator::GetKey()->IsKeyRepeated('D'))
	{
		vecRight = { mSpeed, 0, 0 };
		vecRight = VectorTransform(vecRight, MatrixFromY(goTransform.GetRotYRad()));
	}
	else if (Locator::GetKey()->IsKeyPressed('A') || Locator::GetKey()->IsKeyRepeated('A'))
	{
		vecRight = { -mSpeed, 0, 0 };
		vecRight = VectorTransform(vecRight, MatrixFromY(goTransform.GetRotYRad()));
	}

	auto vel = vecForward + vecRight;
	mVelocity = { VectorX(vel), VectorY(mVelocity), VectorZ(vel) };

	if (Locator::GetKey()->IsKeyPressed('Q') || Locator::GetKey()->IsKeyRepeated('Q'))
	{
		goTransform.SetRotY(goTransform.GetRotY() - mRotSpeed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed('E') || Locator::GetKey()->IsKeyRepeated('E'))
	{
		goTransform.SetRotY(goTransform.GetRotY() + mRotSpeed * Locator::GetTimer()->DeltaTime());
	}

	if (Locator::GetKey()->IsKeyReleased('W') || Locator::GetKey()->IsKeyReleased('S'))
	{
		Vector vec = { 0.0f, VectorY(mVelocity), 0.0f };
		mVelocity = VectorTransform(vec, MatrixFromY(goTransform.GetRotYRad()));
	}

	switch (state)
	{
	case PlayerMotionState::GROUNDED:
	{
		acceleration = 0.0f;
		mVelocity = VectorSetY(mVelocity, 0.0f);
		if (Locator::GetKey()->IsKeyPressed(VK_SPACE))
		{
			goTransform.SetPos(VectorAdd(goTransform.GetPos(), {0.0f, 0.2f, 0.0f}));
			mVelocity = VectorSetY(mVelocity, 20000);
			state = PlayerMotionState::FALLING;
		}
		break;
	}
	case PlayerMotionState::FALLING:
	{
		acceleration += (GRAVITY * mass);
		acceleration -= drag;
		mVelocity = VectorSetY(mVelocity, VectorY(mVelocity) - acceleration);
		break;
	}
	}
	Vector vec3 = mVelocity * dt;
	goTransform.SetPos(goTransform.GetPos() + vec3);

	if (ImGui::Begin("Velocity"))
	{
		ImGui::Text("State: %i", (int)state);
	}
	ImGui::End();

}

PlayerMotionState Player::GetState()
{
	return state;
}

void Player::SetState(PlayerMotionState _state)
{
	state = _state;
}

const Vector& Player::GetVelocity()
{
	return mVelocity;
}
