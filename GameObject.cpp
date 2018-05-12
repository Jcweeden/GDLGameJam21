#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject( int x, int y, int p_width, int p_height, std::string p_textureID) :
    position(x,y), width(p_width), height(p_height), textureID(p_textureID), velocity(0,0), acceleration(0,0)
{

}

void GameObject::draw()
{
  TheTextureManager::Instance()->draw(textureID, (int)position.getX(), (int)position.getY(), width, height, /*m_currentRow, m_currentFrame,*/ TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);

}

void GameObject::update()
{
  velocity += acceleration;
  position += velocity;
};

void GameObject::clean()
{
}