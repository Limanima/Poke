#include "PK_Body.h"
#include "PK_Exceptions.h"
#include "PK_2DSceneControl.h"

namespace PK {

//
PK_Body::PK_Body(PK_eBodyType bodyType, const PK_String &sName) :
  PK_Object(sName)
{
    m_BodyType = bodyType;
    m_pControl = NULL;
} 

//
PK_Body::~PK_Body()
{
}

//
void PK_Body::SetAttachedControl(PK_2DSceneControl *pControl)
{
  if (pControl == m_pControl)
  {
    return;
  }
 
  m_pControl = pControl;

  if (m_pControl == NULL)
  {
    OnControlDettached();
  }
  else
  {
    OnControlAttached(*pControl);
  }
}


//
void PK_Body::OnCollideWithBody(PK_Body &body)
{
    if (m_pControl == NULL)
    {
        return;
    }
    if (m_pControl->OnBodyCollision.HasCallback())
    {
        m_pControl->OnBodyCollision->Execute(body);
    }
}

} // namespace
