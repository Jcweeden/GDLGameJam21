#include "InputHandler.h"

//define static singleton instance
InputHandler* InputHandler::s_pInstance = 0;

InputHandler* InputHandler::Instance()
{
  if(s_pInstance ==0)
    {
      s_pInstance = new InputHandler();
    }

    return s_pInstance;
}


bool InputHandler::isKeyDown(SDL_Scancode key)
{
  if (m_keystates != 0)
  {
    if (m_keystates[key] == 1) {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}


void InputHandler::update()
{
  SDL_Event event;

  while(SDL_PollEvent(&event))
  {
    m_keystates = SDL_GetKeyboardState(0);//update presssed keys

    
    if (event.type == SDL_QUIT)
    {
      std::cout << "InputHandler.cpp: Quit event found\n";
      TheGame::Instance()->quit();
    }

  }
}

void InputHandler::clean()
{
  //no joysticks - unneeded
}