#ifndef _PK_CONSOLEAPP_H_
#define _PK_CONSOLEAPP_H_

#include "PK_String.h"
#include "PK_App.h"
#include "PK_Dictionary.h"

namespace PK {

class PK_AssetManager;

class PK_ConsoleApp : public PK_App
{
    PK_AssetManager         *m_pAssetManager;

public:
	PK_ConsoleApp(const PK_String &sName);
    void InternalInitialize(PK_Dictionary<PK_String, PK_String> arguments);
    virtual void OnShowUsage() {}
    void Exit();
    inline PK_AssetManager & GetAssetManager() { return (*m_pAssetManager); }
};

}
#endif