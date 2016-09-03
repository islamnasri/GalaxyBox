

#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <SFMl\Graphics.hpp>
#include <vector>
#include <string>
#include <Box2D\Box2D.h>


#include "GameConstants.h"
#include "WindowController.h"
#include "CharacterController.h"

using namespace std;

namespace GalaxyBox
{

    struct MyContact {
        b2Fixture *fixtureA;
        b2Fixture *fixtureB;
        bool operator==(const MyContact& other) const
        {
            return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
        }
    };
     
    class ContactListener : public b2ContactListener 
    {
     
    public:
        vector<MyContact> _contacts;
     
        ContactListener();
        ~ContactListener();
     
        virtual void BeginContact(b2Contact* contact);
        virtual void EndContact(b2Contact* contact);
        virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);    
        virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
     
    };
}

#endif