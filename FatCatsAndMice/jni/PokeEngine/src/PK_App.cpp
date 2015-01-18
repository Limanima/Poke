#include "PK_App.h"
#include "PK_Log.h"
#include "PK_ClassFactory.h"
#include "PK_RenderManager.h"

namespace PK {

//
PK_App::PK_App(PK_eAppType type, const PK_String &sName) :
    PK_Component(sName)
{
	SetTypeName("PK_App");
    m_type = type;
}


//
void PK_App::AddComponent(PK_Component & component)
{
    if (m_Components.Contains(&component))
    {
        throw PK_SystemException("Cannot add component because it is already added to the system.", __FILE__, __LINE__);
    }
    component.Grab();
    m_Components.Add(&component);
}

//
void PK_App::InternalInitialize(PK_Dictionary<PK_String, PK_String> arguments)
{
    OnInitialize(arguments);
}

//
void PK_App::InternalRun()
{
    OnRun();
}

//
void PK_App::InternalUnInitialize()
{
    for(int i = (int)m_Components.GetCount() - 1; i >= 0; i--)
	{
        m_Components[i]->OnUnInitialize();
        m_Components[i]->OnUnload();
        m_Components[i]->Release();
    }
    m_Components.Clear();

    OnUnInitialize();
}

// 
void PK_App::UpdateComponents(const PK_GameTimer &time)
{
     for(int i = 0; i < m_Components.GetCount(); i++)
	 {
         if (m_Components[i]->IsActive())
         {
            m_Components[i]->OnUpdate(time);
         }
     }
}

//
void PK_App::DrawComponents(PK_RenderManager &renderer)
{
    renderer.BeginRender();
    for(int i = 0; i < m_Components.GetCount(); i++)
	{
         if (m_Components[i]->IsVisible())
         {
            m_Components[i]->OnDraw();
         }
    }
    renderer.EndRender();
}

} // namespace
