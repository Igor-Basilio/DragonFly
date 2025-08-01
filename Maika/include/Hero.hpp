#ifndef HERO_H
#define HERO_H

#include "../../dragonfly/include/Object.h"
#include "../../dragonfly/include/EventKeyboard.h"

class Hero : public df::Object 
{
    private:
        int move_slowdown = 2;
        int move_countdown;

        void kbd(const df::EventKeyboard *p_keyboard_event);
        void move(df::Vector way);
        void step(void);

    public:
        Hero();
        int eventHandler(const df::Event *p_e) override;
};

#endif 
