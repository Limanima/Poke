#include "PK_DrawableComponent.h"
#include "PK_Scene.h"

namespace PK {
    
PK_DrawableComponent::PK_DrawableComponent()
{
    InitInstance();
	m_pScene = NULL;
}
    
PK_DrawableComponent::PK_DrawableComponent(const PK_String &sName) :
  PK_Component(sName)
{
    InitInstance();
}

//
PK_DrawableComponent::~PK_DrawableComponent()
{
	if (m_pScene != NULL)
	{
		m_pScene->Release();
	}
}

void PK_DrawableComponent::InitInstance()
{
    SetTypeName("PK_Component");
	m_pScene = new PK_Scene(GetName() + "_scene");
	m_pScene->Grab();
}

//
void PK_DrawableComponent::OnInitialize()
{
	PK_Component::OnInitialize();
	m_pScene->InternalInitialize();
}
 
//
void PK_DrawableComponent::OnLoad()
{
	PK_Component::OnLoad();
	m_pScene->InternalLoad();
}


//
void PK_DrawableComponent::OnUpdate(const PK_GameTimer &timer)
{
	PK_Component::OnUpdate(timer);
	m_pScene->InternalUpdate(timer);
}

//
void PK_DrawableComponent::OnUnload()
{
	PK_Component::OnUnload();
	m_pScene->InternalUnload();
}

//
void PK_DrawableComponent::OnDraw()
{
	m_pScene->InternalDraw();
}

} // namespace
