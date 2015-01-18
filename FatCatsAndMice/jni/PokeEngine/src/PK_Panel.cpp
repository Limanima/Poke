#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_Panel.h"

namespace PK {

PK_Panel::PK_Panel(const PK_String &sName) :
    PK_2DSceneControl(sName)
{
	SetTypeName("PK_Panel");
}


} // namespace
