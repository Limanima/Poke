#ifndef _PK_ADBANNERCONTROL_H_
#define _PK_ADBANNERCONTROL_H_

#include "PK_2DSceneControl.h"

// EM STAND BY! A ideia é meter um PK_AdBanner dentro do controlo, o problema e que se o controlo mudar
// tambem e preciso mudar a posicao  tamanho o PK_AdBanner
namespace PK {

class PK_AdBanner;
    
// Classe base para um asset: textura, sprite, font, etc
class PK_AdBannerControl : public PK_2DSceneControl
{
private:
	PK_AdBanner  *m_pBanner;
    
public:
	PK_AdBannerControl(const PK_String &sName, const PK_String &sAdId);
	~PK_AdBannerControl();
    
};

} // namespace

#endif