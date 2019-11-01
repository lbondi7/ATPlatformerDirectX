#include "Bounds.h"

#include <algorithm>

using namespace DirectX;

void Bounds::CalculateBoundingBox(const Vector& pos, const std::vector<Vector>& verts, const Matrix& worldMatrix)
{
	XMFLOAT3 minVert = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVert = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	//auto length = verts.size();
	Vector vec;
	for (size_t i = 0; i < verts.size(); i++)
	{
		vec = verts[i];

		vec = XMVector3Transform(vec, worldMatrix);

		//Get the smallest vertex 
		minVert.x = std::min(minVert.x, XMVectorGetX(vec));
		minVert.y = std::min(minVert.y, XMVectorGetY(vec));
		minVert.z = std::min(minVert.z, XMVectorGetZ(vec));

		//Get the largest vertex 
		maxVert.x = std::max(maxVert.x, XMVectorGetX(vec));
		maxVert.y = std::max(maxVert.y, XMVectorGetY(vec));
		maxVert.z = std::max(maxVert.z, XMVectorGetZ(vec));
	}

	mBBMin = { minVert.x, minVert.y, minVert.z };
	mBBMax = { maxVert.x, maxVert.y, maxVert.z };

	mBBMin = XMVectorAdd(pos, mBBMin);
	mBBMax = XMVectorAdd(pos, mBBMax);
}

bool Bounds::IsInside(const Vector& objBBMinVertex,
	const Vector& objBBMaxVertex)
{
	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
	if (XMVectorGetX(mBBMax) > XMVectorGetX(objBBMinVertex))

		//Is obj1's min X less than obj2's max X? If not, obj1 is to the RIGHT of obj2
		if (XMVectorGetX(mBBMin) < XMVectorGetX(objBBMaxVertex))

			//Is obj1's max Y greater than obj2's min Y? If not, obj1 is UNDER obj2
			if (XMVectorGetY(mBBMax) > XMVectorGetY(objBBMinVertex))

				//Is obj1's min Y less than obj2's max Y? If not, obj1 is ABOVE obj2
				if (XMVectorGetY(mBBMin) < XMVectorGetY(objBBMaxVertex))

					//Is obj1's max Z greater than obj2's min Z? If not, obj1 is IN FRONT OF obj2
					if (XMVectorGetZ(mBBMax) > XMVectorGetZ(objBBMinVertex))

						//Is obj1's min Z less than obj2's max Z? If not, obj1 is BEHIND obj2
						if (XMVectorGetZ(mBBMin) < XMVectorGetZ(objBBMaxVertex))

							//If we've made it this far, then the two bounding boxes are colliding
							return true;

	//If the two bounding boxes are not colliding, then return false
	return false;
}
