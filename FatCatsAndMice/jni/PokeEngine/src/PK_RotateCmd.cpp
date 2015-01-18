#include "PK_RotateCmd.h"
#include "PK_CommandAttributes.h"
#include "PK_2DSceneControl.h"
#include "PK_Exceptions.h"
#include "PK_GameTimer.h"
#include "PK_MathHelper.h"
#include "PK_TypeConverters.h"

#define DIRECTION_CW  -1
#define DIRECTION_CCW  1

namespace PK {

//
PK_RotateCmd::PK_RotateCmd(PK_Script &owner, PK_tRotateCmd &vars) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&vars)
{
	m_Vars = vars;
}

// 
void PK_RotateCmd::Prepare()
{ 
    m_bBreaking = false;    
    m_fCurrentSpeed = 0.0f;
    m_bWrapped = false;
}
    
//               
bool PK_RotateCmd::Execute(const PK_GameTimer &time)
{
    PK_2DSceneControl *p2dControl = Get2DControl();
    if (p2dControl == NULL)
    {
        // FIXME: este comando deve ser aplicavel a objectos 3D
        throw PK_SystemException("Cannot execute 'rotate' command because current object is not a 2D object.", __FILE__, __LINE__);
    }

    float fControlRotation = PK_MathHelper::NormalizeDegreesToPositives(p2dControl->GetRotation()); 
    float fDestRotation = PK_MathHelper::NormalizeDegreesToPositives(m_Vars.destDegrees.GetValue_Float(GetScript()));
    float degreesToRotate = 0.0f; 
    if (m_Vars.direction.GetValue_Int(GetScript()) == DIRECTION_CCW)
    {     
        degreesToRotate = fDestRotation - fControlRotation;
    }
    else 
    {
        degreesToRotate = fControlRotation - fDestRotation;
    }

    if (degreesToRotate < 0)
    { 
        degreesToRotate += 360;
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
        if (fBrakeDistance > abs(degreesToRotate))
        {       
            m_bBreaking = true;
            m_fCurrentSpeed -= (m_Vars.deceleration.GetValue_Float(GetScript()) * (float)time.GetEllapsedTime() / 1000.0f);
            if (m_fCurrentSpeed < 0.0f) 
            {
                p2dControl->SetRotation(m_Vars.destDegrees.GetValue_Float(GetScript()));
                return true;
            }  
        }
    }   
        
    float fSpeed = (m_fCurrentSpeed * (float)time.GetEllapsedTime() / 1000.0f);
    if (fSpeed > degreesToRotate || fSpeed < 0.000001f)
    {
        p2dControl->SetRotation(m_Vars.destDegrees.GetValue_Float(GetScript()));
        return true;
    }

    p2dControl->Rotate(fSpeed * m_Vars.direction.GetValue_Int(GetScript()));

    return false;
}

//
PK_tRotateCmd * PK_RotateCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
   PK_tRotateCmd * pCmd = new PK_tRotateCmd();
   float degrees = PK_TypeConverters::StrToFloat(attributes.GetAttributeValue("to"));
   pCmd->destDegrees.SetValue(PK_MathHelper::NormalizeAngle(degrees));
   pCmd->speed.SetValue_Float(attributes.GetAttribute("speed"));
   pCmd->acceleration.SetValue_Float(attributes.GetAttribute("accel", false));
   pCmd->deceleration.SetValue_Float(attributes.GetAttribute("decel", false));
 

   PK_String sDirection = attributes.GetAttributeValue("direction");
   if (sDirection == "ccw")
   {
       pCmd->direction.SetValue(DIRECTION_CCW);
   }
   else
   if (sDirection == "cw")
   {
       pCmd->direction.SetValue(DIRECTION_CW);
   }
   else
   {
       throw PK_SystemException("Invalid value '%s' for attribute 'direction' in script command 'rotate'. Expected values are 'cw' or 'ccw'.",
                __FILE__, __LINE__, sDirection.c_str());
   }
   return pCmd; 
}


} // namespace