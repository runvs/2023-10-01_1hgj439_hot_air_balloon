
#include "cloud.hpp"
#include <game_interface.hpp>

void Cloud::doCreate()
{
    m_sprite = std::make_shared<jt::Sprite>("assets/cloud.png", textureManager());
}

void Cloud::doUpdate(float const elapsed) { m_sprite->update(elapsed); }
void Cloud::doDraw() const { m_sprite->draw(renderTarget()); }
void Cloud::setPosition(jt::Vector2f const& p) { m_sprite->setPosition(p); }
jt::Vector2f Cloud::getPosition() const { return m_sprite->getPosition(); }
