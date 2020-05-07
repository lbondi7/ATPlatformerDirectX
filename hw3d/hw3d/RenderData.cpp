#include "RenderData.h"

RenderData::~RenderData()
{
	if (p_IndexBuffer) p_IndexBuffer      = nullptr;
	if (p_VertexBuffer) p_VertexBuffer    = nullptr;
	if (p_Texture) p_Texture              = nullptr;
	if (p_Shader) p_Shader                = nullptr;
}
