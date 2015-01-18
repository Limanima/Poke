#include "PK_PlaySoundCmd.h"
#include "PK_CommandAttributes.h"
#include "PK_SoundAsset.h"
#include "PK_Globals.h"
#include "PK_AudioManager.h"

namespace PK {

//
PK_PlaySoundCmd::PK_PlaySoundCmd(PK_Script &owner, PK_tPlaySoundCmd &vars) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&vars)
{
	m_Vars = vars;
}


//
bool PK_PlaySoundCmd::Execute(const PK_GameTimer &time)
{
    PK_SoundAsset *pAsset = PokeEngine.GetAssetManager().LoadSoundEffect(m_Vars.resName.GetValue_Str(GetScript()), PK_ASSET_CONTAINER_NAME);
    PokeEngine.GetAudioManager().PlaySoundEffect(*pAsset);
    return true;
}

//
PK_tPlaySoundCmd * PK_PlaySoundCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
   PK_tPlaySoundCmd * pCmd = new PK_tPlaySoundCmd();
   pCmd->resName.SetValue_Str(attributes.GetAttribute("asset"));

   return pCmd; 
}

} // namespace