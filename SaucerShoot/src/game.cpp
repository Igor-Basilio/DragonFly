
#include "../../dragonfly/include/GameManager.h"
#include "../../dragonfly/include/LogManager.h"
#include "../../dragonfly/include/ResourceManager.h"
#include "../include/Saucer.hpp"
#include "../include/Hero.hpp"

void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {

  if (GM.startUp() != 0)  {
    LM.writeLog("Error starting game manager!");
    return -1;
  }

  loadResources();
  populateWorld();
  GM.run();

  GM.shutDown();

  return 0;
}

void loadResources(void)
{
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    RM.loadSprite("sprites/ship-spr.txt", "hero");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
}

void populateWorld(void)
{
    for(int i=0; i < 5; i++)
        new Saucer;

    new Hero;
}

