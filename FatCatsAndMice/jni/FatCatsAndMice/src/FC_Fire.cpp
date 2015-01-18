#include <PokeEngine.h>
#include "FC_Fire.h"     
#include "FC_Types.h"
#include "FC_Consts.h"
#include "FC_Actor.h"

//
FC_Fire::FC_Fire(const PK::PK_String &sName) :
    PK::PK_Sprite(sName)
{  
    SetTypeName("fc_fire");
    SetSize(768.0f, 200.0f);
    SetTag(ObjectType_Fire);
    SetBackgroundImage(FCAM_SPRITE_FENCE);
    SetBackgroundImageFitMode(PK::ImageSizeMode_SizeControlToImage);
    //SetBackgroundColor(PK_COLOR_RED);

    // Zona de colisão
    m_pCollidingZone = new PK::PK_Panel(GetName() + "_collisionZone");
  //  m_pCollidingZone->SetBackgroundColor(PK_COLOR_GREEN);
    m_pCollidingZone->SetSize(768.0f, 20.0f);
    PK::PK_t2DBodyPartDefinition bodyPartDef;
    bodyPartDef.SetToBox(m_pCollidingZone->GetSize(), GetPivot());
    bodyPartDef.usCollisionMask = (FCAMP_COLLISIONBIT_CAT | FCAMP_COLLISIONBIT_MOUSE); // Colide com gatos e ratos 
    PK::PK_tBodyDefinition bodyDef;
    bodyDef.bodyParts.Add(bodyPartDef);
    bodyDef.bodyType = PK::BodyType_Static;
    bodyDef.shapeMode = PK::ControlBodyShapeMode_UserDefined;
    m_pCollidingZone->SetBodyDefinition(bodyDef);
    m_pCollidingZone->SetWithPhysics(true, PK::BodyType_Static);
    m_pCollidingZone->OnBodyCollision.Set(new PK::PK_BodyCollisionCallback<FC_Fire>(*this, &FC_Fire::ActorCollided));
    AddControl(m_pCollidingZone);
 }

//
void FC_Fire::ActorCollided(PK::PK_Body &body)
{
    PK_2DSceneControl *pControl = body.GetParentControl();

    switch(pControl->GetTag())
    {      
        case ObjectType_Actor:
            FC_Actor *pActor = (FC_Actor *)pControl;
            pActor->Kill(true);
            break;
    }
}
