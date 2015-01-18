#ifndef _PK_PHYSICSMANAGERSETTINGS_H_
#define _PK_PHYSICSMANAGERSETTINGS_H_

#include "PK_Settings.h"
#include "PK_Vector2.h"

namespace PK {

class PK_DataFileRecord;

// Estes settings sao um tanto ou quanto especificos de SDL, talvez um SDLAudioManagerSettings fosse
// mais apropriedado
class PK_PhysicsManagerSettings : public PK_Settings
{
private:
    bool        m_bVisible;
    PK_Vector2  m_vGravity;
    float       m_fPixelsPerMeter;


public:
	PK_PhysicsManagerSettings();
    void OnLoad();
   
	inline bool GetVisible() { return m_bVisible; }
	inline PK_Vector2 GetGravity() { return m_vGravity; }
	inline float GetPixelsPerMeter() { return m_fPixelsPerMeter; }
};

}
#endif
