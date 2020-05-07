#pragma once

#include "Maths.h"
#include "Utilities.h"

class Ray {
public:
	Ray() = default;
	Ray(const Float3& _origin, const Float3& _direction) { 
		m_Origin = _origin;
		
		auto vec = Utilities::ConvertToVec4Dir(_direction);
		vec = DirectX::XMVector4Normalize(vec);

		m_Direction = Utilities::ConvertToFloat3(vec);
		m_InvDirection = {1.0f - m_Direction.x, 1.0f - m_Direction.y , 1.0f - m_Direction.z };
	}
	~Ray() {};

	const Float3& Origin() { return m_Origin; }
	const Float3& Direction() { return m_Direction; }
	const Float3& InvDirection() { return m_InvDirection; }
	float T() { return m_T; }

	const Vec4& OriginV4() { return Utilities::ConvertToVec4Dir(m_Origin); }
	const Vec4& DirectionV4() { return Utilities::ConvertToVec4Dir(m_Direction); }
	const Vec4& InvDirectionV4() { return Utilities::ConvertToVec4Dir(m_InvDirection); }

	void Origin(const Float3& _origin) { m_Origin = _origin; }
	void Direction(const Float3& _direction) { 
		auto vec = Utilities::ConvertToVec4Dir(_direction);
		vec = DirectX::XMVector4Normalize(vec);

		m_Direction = Utilities::ConvertToFloat3(vec);
		m_InvDirection = { 1.0f / m_Direction.x, 1.0f / m_Direction.y , 1.0f / m_Direction.z };
	}
	void T(float _t) { m_T = _t; }

	void Origin(const Vec4& _origin) { m_Origin = Utilities::ConvertToFloat3(_origin); }
	void Direction(const Vec4& _direction) { 
		auto vec = _direction;
		vec = DirectX::XMVector4Normalize(vec);

		m_Direction = Utilities::ConvertToFloat3(vec);
		m_InvDirection = { 1.0f / m_Direction.x, 1.0f / m_Direction.y , 1.0f / m_Direction.z };
	}

private:

	Float3 m_Origin {0.0f, 0.0f, 0.0f};
	Float3 m_Direction { 0.0f, 0.0f, 0.0f };
	Float3 m_InvDirection{ 0.0f, 0.0f, 0.0f };
	float m_T = 0.0f;

};