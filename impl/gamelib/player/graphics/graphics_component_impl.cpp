#include "graphics_component_impl.hpp"
#include <game_properties.hpp>
#include <math_helper.hpp>

GraphicsComponentImpl::GraphicsComponentImpl(std::shared_ptr<jt::GameInterface> gameInterface)
{
    createAnimation(gameInterface->gfx().textureManager());
}

void GraphicsComponentImpl::createAnimation(jt::TextureManagerInterface& textureManager)
{
    m_sprite = std::make_shared<jt::Sprite>("assets/balloon.png", textureManager);
    m_sprite->setOrigin(jt::Vector2f { 16, 10 });
    m_sprite->setOffset(jt::Vector2f { 16, 10 });
}

void GraphicsComponentImpl::updateGraphics(float elapsed) { m_sprite->update(elapsed); }

void GraphicsComponentImpl::setPosition(jt::Vector2f const& playerPosition)
{
    auto spritePosition = playerPosition;
    m_sprite->setPosition(spritePosition);
}

void GraphicsComponentImpl::draw(std::shared_ptr<jt::RenderTargetInterface> target)
{
    m_sprite->draw(target);
}

void GraphicsComponentImpl::flash(float time, jt::Color const& color)
{
    m_sprite->flash(time, color);
}
void GraphicsComponentImpl::setRotation(float angle) { m_sprite->setRotation(angle); }
