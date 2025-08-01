#ifndef BULLET_H
#define BULLET_H

#include "../../dragonfly/include/Object.h"
#include "../../dragonfly/include/EventCollision.h"

class Bullet : df::Object 
{
    private:
        df::Vector starting_pos;

        void out();
        void handle_collision(const df::EventCollision *p_collision_event);

    public:
        Bullet(df::Vector position);
        int eventHandler(const df::Event *p_e) override;
};

#endif 
