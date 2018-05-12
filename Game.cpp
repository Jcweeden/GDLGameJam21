#include "Game.h"
#include <iostream>
#include "SoundMixer.h"
#include "Ball.h"
#include "BounceSurface.h"
#include "CollisionManager.h"

Game* Game::s_pInstance = 0;

Game* Game::Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new Game();
      return s_pInstance;
    }

    return s_pInstance;
  }


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;

  if (fullscreen) {//if method parameter = true then make variable in line below
    flags = SDL_WINDOW_SHOWN;
  }
  
  // initialise SDL
   if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
   {
     std::cout << "Game: SDL init success\n";
     // if succeeded create our window
     m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
 
 // if the window creation succeeded create our renderer
     if(m_pWindow != 0)
     {
       std::cout << "Game: Window creation success\n";
       m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

       if (m_pRenderer != 0) {
         std::cout << "Game: Renderer creation success\n";
         SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
       }
       else {
         std::cout << "Game: Renderer init failed\n";
         return false;
       }
     }
     else
     {
       std::cout << "Game: Window init failed\n";
       return false;
     }
   }
   else
   {
     std::cout << "Game: SDL init failed\n";
     return false; // sdl could not initialise
   }

   std::cout << "Game: Init success\n";
   m_bRunning = true;//start the main loop
   windowWidth = width;
   windowHeight = height;

   loadSounds();
   
   loadTextures();
       
   loadObjects();
   
   return true;
}

void Game::loadSounds()
{
  TheSoundMixer::Instance()->load("assets/changeDirection.wav", "spaceBar", SOUND_SFX);
  TheSoundMixer::Instance()->load("assets/space.wav", "hitPaddle", SOUND_SFX);
  TheSoundMixer::Instance()->load("assets/death.wav", "death", SOUND_SFX);
}

void Game::loadTextures()
{
  TheTextureManager::Instance()->load("assets/blue.png", "ball", m_pRenderer);
  TheTextureManager::Instance()->load("assets/white.png", "whiteWall", m_pRenderer);
  TheTextureManager::Instance()->load("assets/red.png", "redWall", m_pRenderer);
  TheTextureManager::Instance()->load("assets/overlayscreen.png", "overlayFilter", m_pRenderer);
  //TheTextureManager::Instance()->load("assets/overlay.png", "overlay", m_pRenderer);
}

void Game::loadObjects()
{
  ball = new Ball((windowWidth/2),30,22,22,"whiteWall", 4, NONE);
      //m_gameObjects.push_back();

  int borderWidth = 10;
  //w=640
  m_gameObjects.push_back(new BounceSurface(0,(windowHeight-borderWidth), windowWidth,borderWidth,"whiteWall",1,2)); //bottom wall
  m_gameObjects.push_back(new BounceSurface(0,0, windowWidth,borderWidth,"whiteWall",1,2)); //top wall

  m_gameObjects.push_back(new BounceSurface(0,borderWidth, borderWidth,(windowHeight-borderWidth-borderWidth),"redWall",1,1)); //right wall
  m_gameObjects.push_back(new BounceSurface((windowWidth-borderWidth),borderWidth, borderWidth,(windowHeight-borderWidth-borderWidth),"redWall",1,1)); //left wall

 screenOverlay = new GameObject(0,0, windowWidth,windowHeight,"overlayFilter",1,0); //Texture on screen

}

void Game::render()
{
  SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

  for(size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->draw(/*m_pRenderer*/);
  }
  ball->draw();
  screenOverlay->draw();
  
  SDL_RenderPresent(m_pRenderer);  //draw to the screen
}

void Game::update() {
  //   m_currentFrame = int(((SDL_GetTicks() /100) % 6));

   //loop through and update our objects
   for(size_t i = 0; i < m_gameObjects.size(); i++)
   {
     m_gameObjects[i]->update();
   }
   ball->update();
        

   //loop through objects and check for collisions against the ball
   TheCollManager::Instance()->checkForCollsionsAgainstBall(ball, m_gameObjects);
}

void Game::clean() {
  std::cout << "Game: cleaning game\n";

  //TheInputHandler::Instance()->clean();//remove any controller connections

  
  SDL_DestroyWindow (m_pWindow);
  SDL_DestroyRenderer (m_pRenderer);
  SDL_Quit();
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();
}

void Game::quit() {
  m_bRunning = false;
}
