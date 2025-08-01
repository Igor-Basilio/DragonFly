
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
    RM.loadSprite("sprites/hero-spr.txt", "hero");
}

void populateWorld(void)
{
    new Hero;
}

