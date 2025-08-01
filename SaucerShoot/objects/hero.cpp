
#include "../include/Hero.hpp"
#include "../../dragonfly/include/LogManager.h"
#include "../../dragonfly/include/WorldManager.h"
#include "../../dragonfly/include/GameManager.h"
#include "../../dragonfly/include/EventStep.h"
#include "../include/Bullet.hpp"

Hero::Hero()
{
    int err = setSprite("hero");
    if(err)
    {
        LM.writeLog("Hero::Hero(): Failed to set sprite: 'hero'");
    }

    err = registerInterest(df::KEYBOARD_EVENT);
    if(err)
        LM.writeLog("Hero::Hero(): Failed to register interest: 'KEYBOARD_EVENT'");

    err = registerInterest(df::STEP_EVENT);
    if(err)
        LM.writeLog("Hero::Hero(): Failed to register interest: 'STEP_EVENT'");

    (void) setType("Hero");
    float world_v = WM.getBoundary().getVertical();
    err = setPosition( df::Vector(2 * getBox().getHorizontal(), world_v/2) );
    if(err)
    {
        LM.writeLog("Hero::Hero(): Failed to set start "
                "position for 'Hero' Object"); 
    }
}

int Hero::eventHandler(const df::Event *p_e) 
{
    auto type = p_e->getType();
    if(type == df::KEYBOARD_EVENT)
    {
        const df::EventKeyboard *p_keyboard_event =
            dynamic_cast <const df::EventKeyboard *> (p_e);
        kbd(p_keyboard_event);
        return 1;
    }else if(type == df::STEP_EVENT)
    {
        step();   
        return 1;
    }
    return 0;
}

void Hero::kbd(const df::EventKeyboard *p_keyboard_event)
{
   switch(p_keyboard_event->getKey())
   {
       case df::Keyboard::Q:
           if(p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
               GM.setGameOver();
       break;

       case df::Keyboard::W:
            if(p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                move(-1);
       break;

       case df::Keyboard::S:
            if(p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                move(+1);
       break;

       case df::Keyboard::SPACE:
            if(p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            {
                df::Vector bullet_pos(getPosition().getX() + getBox().getHorizontal(), 
                        getPosition().getY());
                new Bullet(bullet_pos);
            }
       break;

       default:
       break;
   }
}

void Hero::move(int dy)
{
    if(move_countdown > 0)
        return;
    move_countdown = move_slowdown;

    df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);

    if( (new_pos.getY() <=
         WM.getBoundary().getVertical() - getBox().getVertical() / 2)
       && new_pos.getY() >= 1)
    {
        WM.moveObject(this, new_pos);
    }
}

void Hero::step(void)
{
    move_countdown--;
    if(move_countdown < 0)
        move_countdown = 0;
}

