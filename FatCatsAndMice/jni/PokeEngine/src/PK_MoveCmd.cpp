#include "PK_MoveCmd.h"
#include "PK_CommandAttributes.h"
#include "PK_2DSceneControl.h"
#include "PK_Exceptions.h"
#include "PK_GameTimer.h"

namespace PK {

//
PK_MoveCmd::PK_MoveCmd(PK_Script &owner, PK_tMoveCmd &vars) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&vars)
{
	m_Vars = vars;
}

//
void PK_MoveCmd::Prepare()
{
    m_fCurrentSpeed = m_Vars.speed.GetValue_Float(GetScript());
    if (!m_Vars.acceleration.IsNull(GetScript()))
    {
        m_fCurrentSpeed = 0.0f;
    }

    if (!m_Vars.by.IsNull(GetScript()))
    {
        PK_2DSceneControl *p2dControl = Get2DControl();
        PK_Vector2 v = p2dControl->GetPosition() - m_Vars.by.GetValue_Vector2(GetScript());
        m_Vars.destination.SetValue(v);
    }

    m_bBreaking = false;
}

//
bool PK_MoveCmd::Execute(const PK_GameTimer &time)
{
    PK_2DSceneControl *p2dControl = Get2DControl();
    if (p2dControl == NULL)
    {
        // FIXME: este comando deve ser aplicavel a objectos 3D
        throw PK_SystemException("Cannot execute 'move' command because current object is not a 2D object.", __FILE__, __LINE__);
    }
	     
    // Calculo do vector direcao
    // Destino - posicao corrente
    PK_Vector2 direction = m_Vars.destination.GetValue_Vector2(GetScript()) - p2dControl->GetPosition();
    // Calculo da distancia a andar
    float distToDest = glm::length(direction);
    if (distToDest == 0)
    {
        return true;
    }
         
    // Calculo da velocidade
    if (!m_bBreaking)
    {
        if (!m_Vars.acceleration.IsNull(GetScript()))
        { 
            m_fCurrentSpeed += m_Vars.acceleration.GetValue_Float(GetScript()) * (float)time.GetEllapsedTime() / 1000.0f;
            if (m_fCurrentSpeed > m_Vars.speed.GetValue_Float(GetScript()))
            {
                m_fCurrentSpeed = m_Vars.speed.GetValue_Float(GetScript());
            }
        }
        else
        {
            m_fCurrentSpeed = m_Vars.speed.GetValue_Float(GetScript());
        } 
    }
            
    if (!m_Vars.deceleration.IsNull(GetScript()))
    {
        float fBrakeDistance = (m_fCurrentSpeed * m_fCurrentSpeed) / (2 * m_Vars.deceleration.GetValue_Float(GetScript()));
        // Temos que ver se e altura de travar
        if (fBrakeDistance > distToDest)
        {  
            m_bBreaking = true;
            m_fCurrentSpeed -= (m_Vars.deceleration.GetValue_Float(GetScript()) * (float)time.GetEllapsedTime() / 1000.0f);
            if (m_fCurrentSpeed < 0.0f)
            {
                p2dControl->SetPosition(m_Vars.destination.GetValue_Vector2(GetScript()));
                return true;
            }
        }
    }
          
    float fSpeed = m_fCurrentSpeed * (float)time.GetEllapsedTime() / 1000.0f;
    // Normalizamos e multiplicamos pela velocidade para termos o vector que vamos somar a posicao actual 
    direction = glm::normalize(direction);
    direction *= fSpeed;

    float distToMove = glm::length(direction);
    if (distToMove < distToDest)
    {
        p2dControl->Move(direction);
    }
    else
    {
        p2dControl->SetPosition(m_Vars.destination.GetValue_Vector2(GetScript()));
        return true;
    }
    
    return false;
}

//
PK_tMoveCmd * PK_MoveCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
   PK_tMoveCmd * pCmd = new PK_tMoveCmd();

   pCmd->destination.SetValue_Vector2(attributes.GetAttribute("to", false));
   pCmd->by.SetValue_Vector2(attributes.GetAttribute("by", false));
   if (!pCmd->destination.IsNull() &&
       !pCmd->by.IsNull())
   {
       throw PK_SystemException("Cannot use 'to' and 'by' in the same 'move' command.", __FILE__, __LINE__);
   }
   if (pCmd->destination.IsNull() &&
       pCmd->by.IsNull())
   {
       throw PK_SystemException("'to' or 'by' arguments are mandatory in the 'move' command.", __FILE__, __LINE__);
   }
   pCmd->speed.SetValue_Float(attributes.GetAttribute("speed"));
   pCmd->acceleration.SetValue_Float(attributes.GetAttribute("accel", false));
   pCmd->deceleration.SetValue_Float(attributes.GetAttribute("decel", false));
  
   return pCmd; 
}

} // namespace