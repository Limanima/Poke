#ifndef _PK_LEADERBOARD_H_
#define _PK_LEADERBOARD_H_

#include "PK_String.h"
#include "PK_Object.h"


namespace PK {
    
// Classe base para um asset: textura, sprite, font, etc
class PK_Leaderboard : public PK_Object
{
private:
    PK_String m_sId; // O identificador no Game Center ou no Google Play

protected:
	PK_Leaderboard(const PK_String &sName, const PK_String &sId);

public:
    virtual bool CanSubmitScore();
    virtual bool CanShow();
	virtual bool SubmitScore(int iScore);
    virtual bool Show();
    virtual bool IsSupported();
    
    inline PK_String GetId() { return m_sId; }

    static PK_Leaderboard * CreateInstance(const PK_String &sName, const PK_String &sIdGameCenter, const PK_String &sIdGooglePlay);
};

} // namespace

#endif
