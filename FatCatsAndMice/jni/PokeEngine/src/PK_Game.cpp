#include "PK_Globals.h"
#include "PK_Game.h"
#include "PK_AppStore.h"

#if defined(POKE_ANDROID)
  #include "PK_AndroidActivity.h"
  #include "PK_AndroidAppStore.h"
#elif defined(POKE_IOS)
  #include "iOS/PKc_CInterface.h"
#endif

namespace PK
{
    
PK_Game::PK_Game(const PK_String &sName):
    PK_Component(sName)
{
    SetTypeName("PK_Game");
}
    
//
void PK_Game::OpenInAppStore()
{
	PK_AppStore::OpenAppPage(GetAppStoreId());
}
 
//
void PK_Game::OnInitialize()
{
#if defined(POKE_ANDROID)
	m_sStoreId = PK_AndroidActivity::GetPackageName();
#else
    m_sStoreId = PokeEngine.GetSettings().GetAppId();
#endif
}
	
//
void PK_Game::Exit()
{
	PokeEngine.ExitGame();
}

//
bool PK_Game::OnClose()
{
    return true;
}

//
PK_SceneControl * PK_Game::CreateControl(const PK_String &typeName, const PK_String &sName)
{
    throw PK_SystemException("Method CreateControl() must be overriden in PK_Game.", __FILE__, __LINE__);
}

} // namespace
