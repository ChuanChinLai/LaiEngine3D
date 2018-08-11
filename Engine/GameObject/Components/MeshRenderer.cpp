#include "MeshRenderer.h"

#include <Engine\Graphics\Mesh.h>

void LaiEngine::MeshRenderer::Update()
{
	m_pMesh->Render();
}

void LaiEngine::MeshRenderer::SetMesh(Graphics::Mesh * mesh)
{
	m_pMesh = mesh;
}
