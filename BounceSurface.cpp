#include "BounceSurface.h"

BounceSurface::BounceSurface(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType)
    :GameObject(x, y, p_width, p_height, textureID, p_numFrames, p_resultOfCollisionType), resultOfCollisionType(p_resultOfCollisionType)
{
  
}

void BounceSurface::draw()
{
  GameObject::draw();
}

void BounceSurface::update()
{
  GameObject::update(); 
}

void BounceSurface::clean(){}

