#include "PK_Globals.h"
#include "PK_ConsoleApp.h"
#include "PK_Console.h"
#include "PK_ClassFactory.h"

namespace PK {

//
PK_ConsoleApp::PK_ConsoleApp(const PK_String &sName) :
    PK_App(AppType_Console, sName)
{
	SetTypeName("PK_ConsoleApp");
}

//
void PK_ConsoleApp::InternalInitialize(PK_Dictionary<PK_String, PK_String> arguments)
{
    // Asset Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating asset manager...");
    m_pAssetManager = PK_ClassFactory::CreateAssetManager(PK_ASSET_MANAGER_NAME);
	AddComponent(*(PK_Component * )m_pAssetManager);
     
    for(int i = 0; i < GetComponents().GetCount(); i++)
	{
        PK_Log::WriteInfo(PK_LOG_TAG, "Initialize component '%s'", GetComponents()[i]->GetName().c_str());
        GetComponents()[i]->OnLoad();
        GetComponents()[i]->OnInitialize();
    }

    try
    {
        PK_App::InternalInitialize(arguments);
    }
    catch(PK_InvalidAppArgumentsException &ex)
    {
        OnShowUsage();
        PK_Console::WriteLine(ex.GetMsg());
        Exit();
    }
}

    
//
void PK_ConsoleApp::Exit()
{
    ::exit(0);
}

} // namespace
