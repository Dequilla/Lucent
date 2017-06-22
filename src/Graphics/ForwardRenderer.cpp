#include "ForwardRenderer.h"

ce::graphics::ForwardRenderer::ForwardRenderer()
{
	setScreenBufferSize(core::Application::getInstance().screenWidth, core::Application::getInstance().screenHeight);
	init();
}

ce::graphics::ForwardRenderer::ForwardRenderer(unsigned int width, unsigned int height)
{
	setScreenBufferSize(width, height);
	init();
}

void ce::graphics::ForwardRenderer::init()
{
	m_commandQueue.reserve(1000);

	//
	// uniforms?
	//
}

void ce::graphics::ForwardRenderer::begin()
{
	glViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);

	m_commandQueue.clear();
}

void ce::graphics::ForwardRenderer::beginScene(Camera* camera)
{
	m_projectionMatrix = camera->getProjectionMatrix();
	m_viewMatrix = camera->getViewMatrix();
	m_cameraPosition = camera->getPosition();
}

void ce::graphics::ForwardRenderer::submit(const RenderCommand& command)
{
	m_commandQueue.push_back(command);
}

void ce::graphics::ForwardRenderer::submitMesh(Mesh* mesh, const glm::mat4& transform)
{
	RenderCommand command;
	command.mesh = mesh;
	command.transform = transform;
	// TODO: command.shader = mesh->GetMaterialInstance()->GetMaterial()->GetShader();
	submit(command);
}

void ce::graphics::ForwardRenderer::submitLightSetup(LightSetup& setup)
{
	m_lights = setup;
}

void ce::graphics::ForwardRenderer::endScene()
{
}

void ce::graphics::ForwardRenderer::end()
{
	// TODO: Sorting and batching things that belong together
}

void ce::graphics::ForwardRenderer::present()
{
	/*
	
	foreach command in m_commandQueue:
		Material* material = command.mesh->getMaterial();
		int materialRenderFlags = material.getFlags();
		give shader all the uniforms etc
		render(mesh);
		
	*/
}