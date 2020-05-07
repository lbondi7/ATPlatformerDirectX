#pragma once

#include "Buffer.h"
#include "Texture.h"
#include "Shader.h"
#include "InstanceData.h"

struct RenderData
{

	~RenderData();

	Buffer m_VertexBuffer;
	Buffer m_IndexBuffer;
	Buffer m_MatrixBuffer;
	Buffer m_LightBuffer;

	UINT m_IndexCount = 0;
	UINT m_VertexCount = 0;

	bool m_DrawIndexed = true;
	bool m_DrawInstanced = false;

	D3D_PRIMITIVE_TOPOLOGY m_Topolgy = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	Texture m_Texture;
	//Shaders m_Shader;

	Buffer* p_VertexBuffer = nullptr;
	Buffer* p_IndexBuffer = nullptr;

	std::unique_ptr<Buffer> up_MatrixBuffer;
	std::unique_ptr<Buffer> up_LightBuffer;
	std::unique_ptr<Buffer> up_InstanceBuffer;

	Texture* p_Texture = nullptr;
	Shaders* p_Shader = nullptr;

	std::unique_ptr<InstanceData> up_InstanceData;

};