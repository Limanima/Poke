#ifndef _PK_MESSAGERECEIVER_H_
#define _PK_MESSAGERECEIVER_H_

namespace PK {
#include "PK_Types.h"

// 
class PK_MessageReceiver 
{
public:
	virtual void OnMessageReceived(PK_tMessage1 &msg) = 0;
};

} // namespace

#endif