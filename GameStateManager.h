#ifndef _GAMESTATEMAN_
#define _GAMESTATEMAN_

#include "GameState.h"
#include <iostream>
#include <vector>

//class GameState;


class GameStateManager {
public:
   void pushState(GameState* pState);
   void changeState(GameState* pState);
   void popState();

   void update();
   void render();

private:
  std::vector<GameState*> gameStates;
};

#endif
