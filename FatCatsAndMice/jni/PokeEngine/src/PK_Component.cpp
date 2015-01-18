#include "PK_Component.h"
#include "PK_String.h"

namespace PK {
    
//
PK_Component::PK_Component(const PK_String &sName) :
  PK_Object(sName)
{
    SetTypeName("PK_Component");
	m_bActive = true;
	m_bVisible = true;
    m_pParent = NULL;
}

//
PK_Component::~PK_Component()
{
  SetParent(NULL);
}

//
void PK_Component::SetParent(PK_Object * pObject)
{
  if (m_pParent != NULL)
  {
    m_pParent->Release();
  }
  m_pParent = pObject;
  if (m_pParent != NULL)
  {
    m_pParent->Grab();
  }
}

//
void PK_Component::InternalOnEnterBackground()
{
   OnEnterBackground();
}

//
void PK_Component::InternalOnEnterForeground()
{
   OnEnterForeground();
}

} // namespace
