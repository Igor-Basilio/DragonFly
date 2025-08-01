
#include "../include/Saucer.hpp"
#include "../../dragonfly/include/LogManager.h"
#include "../../dragonfly/include/WorldManager.h"
#include "../../dragonfly/include/EventOut.h"

Saucer::Saucer()
{
    int err = setSprite("saucer");
    if(err)
    {
        LM.writeLog("Saucer::Saucer(): Failed to set sprite: 'saucer'");
    }

    (void) setType("Saucer");
    (void) setVelocity(df::Vector(-0.25, 0));

    err = moveToStart();
    if(err)
    {
        LM.writeLog("Saucer::Saucer(): Failed to set start "
                "position for 'Saucer' Object"); 
    }
}

int Saucer::eventHandler(const df::Event *p_e)
{
    if (p_e->getType() == df::OUT_EVENT)
    {
        out();
        return 1;
    }
    return 0;
}

void Saucer::out()
{
   if(getPosition().getX() >= 0)
       return;
   moveToStart();
}

int Saucer::moveToStart()
{
    int world_h = WM.getBoundary().getHorizontal();
    int world_v = WM.getBoundary().getVertical();

    int object_h = getBox().getHorizontal();
    int object_v = getBox().getVertical();

    int x_pos  = world_h + object_h + rand() % world_h; 
    int modulo = (world_v - object_v) >= 0 ? world_v - object_v : 0;

    int y_pos = rand() % modulo;
    int err = WM.moveObject(this, df::Vector(x_pos, y_pos));
    return err;
}

