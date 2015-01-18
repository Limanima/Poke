#ifndef _PK_ANDROIDLEADERBOARD_H_
#define _PK_ANDROIDLEADERBOARD_H_

#include "PK_Leaderboard.h"
#include <jni.h>

namespace PK {
   
// Classe base para um asset: textura, sprite, font, etc
class PK_AndroidLeaderboard : public PK_Leaderboard
{
	jobject m_javaObject;
	jclass  m_javaClass;
	jmethodID m_showMethod;
	jmethodID m_submitScoreMethod;

public:
	PK_AndroidLeaderboard(const PK_String &sName, const PK_String &sIdGooglePlay);
	~PK_AndroidLeaderboard();

	bool SubmitScore(int iScore);
    bool Show();
    bool CanSubmitScore();
    bool CanShow();
    bool IsSupported();

private:
    void CreateJavaObject();
};

} // namespace

#endif
