#ifndef _PK_BOX2DCONTACTLISTENER_H_
#define _PK_BOX2DCONTACTLISTENER_H_

#include <box2d/box2d.h>

namespace PK {
 
class PK_PhysicsManager;

class PK_Box2DContactListener : public b2ContactListener
{
private:
    PK_PhysicsManager *m_pManager;


public:
    PK_Box2DContactListener(PK_PhysicsManager &manager);
 
    void BeginContact(b2Contact* contact); 
    void EndContact(b2Contact* contact);
};

}

#endif
