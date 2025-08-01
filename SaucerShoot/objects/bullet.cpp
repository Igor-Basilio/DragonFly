
#include "../include/Bullet.hpp"
#include "../../dragonfly/include/LogManager.h"
#include "../../dragonfly/include/WorldManager.h"
#include "../../dragonfly/include/EventOut.h"
#include "../include/Saucer.hpp"

Bullet::Bullet(df::Vector position) : starting_pos(position)
{
    int err = setSprite("bullet");
    if(err)
    {
        LM.writeLog("Bullet::Bullet(): Failed to set sprite: 'bullet'");
    }

    (void) setType("Bullet");
    (void) setVelocity(df::Vector(1.5, 0));

    err = setPosition(starting_pos);
    if(err)
    {
        LM.writeLog("Bullet::Bullet(): Failed to set start "
                "position for 'Bullet' Object"); 
    }
}

int Bullet::eventHandler(const df::Event *p_e)
{
    auto type = p_e->getType();
    if(type == df::OUT_EVENT)
    {
        out();
        return 1;
    }
    else if(type == df::COLLISION_EVENT)
    {
        auto *p_collision_event =
            dynamic_cast<const df::EventCollision*> (p_e);
        handle_collision(p_collision_event);
        return 1;
    }
    return 0;
}

void Bullet::handle_collision(const df::EventCollision *p_collision_event)
{
   auto *obj2 = p_collision_event->getObject2(); 
   if(obj2->getType() == "Saucer")
   {
       Saucer *s = dynamic_cast<Saucer*>(obj2);         
       s->moveToStart();
       delete this;
   }
}

void Bullet::out(void)
{
    if(getPosition().getX() + getBox().getHorizontal() > 
            WM.getBoundary().getHorizontal() )
    {
        delete this;
    }
}

