#include "FC_GameSession.h"
#include "FC_GameSettings.h"
#include "FC_Game.h"
#include "FC_Actor.h"
#include "FC_CatActor.h"
#include "FC_DogActor.h"
#include "FC_MouseActor.h"
#include "FC_InanimateActor.h"
#include "FC_Consts.h"
 
#define SESSION_FILE "fatCats.session"
   
// 
FC_GameSession::FC_GameSession()
{
    m_iGamesPlayed = 0;
    m_iHighScore = 0;
    m_bAutologin = false;
    m_bAskedToLogin = false;
    m_bAudioOn = true;
    m_iTutorialSeenCount = 0;
    Reset();
    m_sFilename = PK::PK_Path::Combine(PK::PK_Environment::GetGameStoragePath(), PK::PK_String(SESSION_FILE));
}       


// 
void FC_GameSession::Save()
{
    PK::PK_DataFileRecord *pRoot = new PK::PK_DataFileRecord("fatCats.session");
    pRoot->AddField("highScore", m_iHighScore);
    pRoot->AddField("autoLogin", m_bAutologin);
    pRoot->AddField("gamesPlayed", m_iGamesPlayed);
    pRoot->AddField("audioOn", m_bAudioOn);
    pRoot->AddField("tutorialSeenCount", m_iTutorialSeenCount);

    PK::PK_DataFile file;
    file.SetRoot(pRoot);
    PK::PK_XmlDataFileWriter writer;
    writer.Write(file, m_sFilename);
}

// 
void FC_GameSession::Load()
{
    Reset();
    if (!PK::PK_File::Exists(m_sFilename))
    {
        return;
    }
    PK::PK_DataFile file;
    PK::PK_XmlDataFileReader reader;
    reader.Load(file, m_sFilename);
    if (file.GetRoot() == NULL)
    {
        return;
    }

    m_iHighScore = file.GetRoot()->GetFieldValue_Int("highScore", 0);
    m_bAutologin = file.GetRoot()->GetFieldValue_Bool("autoLogin", false);
    m_iGamesPlayed = file.GetRoot()->GetFieldValue_Int("gamesPlayed", 0);
    m_bAudioOn = file.GetRoot()->GetFieldValue_Bool("audioOn", true);
    m_iTutorialSeenCount = file.GetRoot()->GetFieldValue_Int("tutorialSeenCount", 0);
}

//
void FC_GameSession::Reset()
{ 
   m_iDeliveredAnimals = 0;
   m_iScore = 0;
   m_bFridgeWasReleased = false;
   m_bElephantWasReleased = false;    
   m_iNoDogsCounter = 0;
   m_iNoInanimateCounter = 0;
   m_iNoShirtCounter = 0;
   m_uiEllapsedTime = 0;
   m_fDogsProbability = 10.0f;
   m_fObjectsProbability = 10.0f;
}

//
void FC_GameSession::IncrementDelivered()
{
    m_iDeliveredAnimals++;
}

//
void FC_GameSession::AddScore(int iScore)
{
    m_iScore += iScore;
}

//
void FC_GameSession::AddEllapsedTime(unsigned int uiEllapsed)
{
    m_uiEllapsedTime += uiEllapsed;
}

//
const bool FC_GameSession::IsLevelValid(FC_eTimmingLevel level)
{
    FC_GameSettings *pSettings = &FC_Game::GetInstance().GetSettings();
    FC_tTimmingEntry * pEntry = pSettings->GetLevelEntry(level); 
    return (pEntry->_iTimeInMsecs < (int)GetEllapsedTime());
}

//
FC_Actor * FC_GameSession::RandomizeActor()
{
    PK::PK_Array<FC_eActorType> actorTypesToRandomize;
    FC_Actor *pActorToRelease = NULL;
    // Criar um array com os elementos que vao ser sorteados
    // 10 ratos, 10 gatos, 1 cao e 1 objecto inanimado
    actorTypesToRandomize.SetSize(10);
    // Pares gatos, impares ratos
    for(int i = 0; i < 10; i++)
    {
		if (i % 2 == 0)
		{
			actorTypesToRandomize[i] = ActorType_Cat;
		}
		else
		{
			actorTypesToRandomize[i] = ActorType_Mouse;
		}
    }
    // Caes e por settings
    if (IsLevelValid(TimmingLevel_Dog))
    {
		if (m_iNoDogsCounter != -1) // -1 significa que o ultimo a sair era um cao, so para n sairem 2 seguidos
		{
			actorTypesToRandomize.Add(ActorType_Dog);
			// Quanto mais tempo sem sair cao, maior probabilidade
            // m_fDogsProbability decrementa ao longo do tempo, assim comecam a sair cada vez mais caes
			int probIncrease = (m_iNoDogsCounter / (int)m_fDogsProbability);
			for(int i = 0; i < probIncrease; i++)
			{
				actorTypesToRandomize.Add(ActorType_Dog);
			}
		}
		else
		{
		   m_iNoDogsCounter = 0;
		}
        m_fDogsProbability -= 0.1f;
        if (m_fDogsProbability < 4)
        {
            m_fDogsProbability = 4;
        }
    }
    // Objectos e por settings
    if (IsLevelValid(TimmingLevel_Inanimate))
    {
		if (m_iNoInanimateCounter != -1)
		{
			actorTypesToRandomize.Add(ActorType_Object);
			// Quanto mais tempo sem sair cao, maior probabilidade
			int probIncrease = (m_iNoInanimateCounter / (int)m_fObjectsProbability);
			for(int i = 0; i < probIncrease; i++)
			{
				actorTypesToRandomize.Add(ActorType_Object);
			}
            m_fObjectsProbability -= 0.1f;
            if (m_fObjectsProbability < 4)
            {
                m_fObjectsProbability = 4;
            }
		}
		else
		{
		   m_iNoInanimateCounter = 0;
		}
    }
    int i = PK::PK_RandomGenerator::GetRandNumber(actorTypesToRandomize.GetSize());
    FC_eActorType actorTypeToRelease = actorTypesToRandomize[i];
     //actor = ActorType_Object;
    switch(actorTypeToRelease)
    {
        case ActorType_Cat:
            {
                PK::PK_Array<int> cats;
                cats.Add(0);
                if (IsLevelValid(TimmingLevel_Cat2))
                {
                    cats.Add(1);
                }
                if (IsLevelValid(TimmingLevel_Cat3))
                {
                    cats.Add(2);
                }

                int iCatNr = PK::PK_RandomGenerator::GetRandNumber(cats.GetSize());
                pActorToRelease = &PK::PokeEngine.GetLibrary().GetControlInstance<FC_CatActor>(FCAM_LIB_ITEM_CAT_IDX + cats[iCatNr]);
            }
            break;

        case ActorType_Mouse:
            {
                PK::PK_Array<int> mice;
                mice.Add(0);
                if (IsLevelValid(TimmingLevel_Mouse2))
                {
                     mice.Add(1);
                }
                if (IsLevelValid(TimmingLevel_Mouse3))
                {
                    mice.Add(2);
                }

                int iMouseNr = PK::PK_RandomGenerator::GetRandNumber(mice.GetSize());
                pActorToRelease = &PK::PokeEngine.GetLibrary().GetControlInstance<FC_MouseActor>(FCAM_LIB_ITEM_MOUSE_IDX + mice[iMouseNr]);    
            }
            break;

        case ActorType_Dog:
            pActorToRelease = &PK::PokeEngine.GetLibrary().GetControlInstance<FC_DogActor>(FCAM_LIB_ITEM_DOG_IDX);
            m_iNoDogsCounter = -1; // para impedir que saiam 2 caes seguidos
            break;

        case ActorType_Object:
            {
                PK::PK_Array<int> inanimate;
                inanimate.Add(FCAM_CHEESE);
                inanimate.Add(FCAM_FISH);
                if (!m_bFridgeWasReleased)
                {
                    inanimate.Add(FCAM_FRIDGE);
                }
                if (!m_bElephantWasReleased)
                {
                    inanimate.Add(FCAM_ELEPHANT);
                }
                FC_InanimateActor *pInanimate = &PK::PokeEngine.GetLibrary().GetControlInstance<FC_InanimateActor>(FCAM_LIB_ITEM_OBJECT_IDX);
                int iObjNr = inanimate[PK::PK_RandomGenerator::GetRandNumber(inanimate.GetSize())];
                pInanimate->SetInanimteType(iObjNr);
                if (iObjNr == FCAM_FRIDGE)
                {
                    m_bFridgeWasReleased = true;
                }
                if (iObjNr == FCAM_ELEPHANT)
                {
                    m_bElephantWasReleased = true;
                }
           
                pActorToRelease = pInanimate;
				m_iNoInanimateCounter = -1;  // para impedir que saiam 2 seguidos
            }
            break;

		default:
			PK::PK_Log::WriteWarning(FCAM_LOG_TAG, "Unexpected actor type %d.", actorTypeToRelease);
			return NULL;
    }
    
    // Com t-shirt?
    if(pActorToRelease->CanWearShirt() && IsLevelValid(TimmingLevel_Shirts))
    {
		int shirtProbability = FC_Game::GetInstance().GetSettings().GetShirtProbability();
		shirtProbability -= (m_iNoShirtCounter / shirtProbability);
		if (shirtProbability < 1)
		{
			shirtProbability = 1;
		}
#ifdef POKE_DEBUG
		PK::PK_Log::WriteInfo(FCAM_LOG_TAG, "Probabilidade t-shirt: 1 para %d", shirtProbability);
#endif
        if (PK::PK_RandomGenerator::GetRandNumber(shirtProbability) == 0)
        {
            pActorToRelease->SetWithShirt(true);
			m_iNoShirtCounter = 0;
        }
		else
		{
			m_iNoShirtCounter++;
		}
    }

	if (actorTypeToRelease != ActorType_Dog && IsLevelValid(TimmingLevel_Dog))
	{
		m_iNoDogsCounter++;
	}
	if (actorTypeToRelease != ActorType_Object && IsLevelValid(TimmingLevel_Inanimate))
	{
		m_iNoInanimateCounter++;
	}

#if POKE_DEBUG
	PK::PK_String probTrace = "Array probabilidades: ";
	PK::PK_String tmp;
    for(int i = 0; i < (int)actorTypesToRandomize.GetCount(); i++)
	{
		tmp.Format("%d", actorTypesToRandomize[i]);
		probTrace += tmp + ",";
	}
    tmp.Format(" Sorteado=%d", (int)actorTypeToRelease);
    probTrace += tmp;
	PK::PK_Log::WriteInfo(FCAM_LOG_TAG, probTrace);
#endif

    return pActorToRelease;
}

//
void FC_GameSession::Trace()
{
    PK::PK_Log::WriteInfo(FCAM_LOG_TAG, "Session-> Time:%d, Score:%d, Delivered:%d", GetEllapsedTime(), GetScore(), GetDelivered());
}

//
bool FC_GameSession::ShouldShowTutorial()
{
    return (m_iHighScore < 7 && m_iTutorialSeenCount < 3);
}

