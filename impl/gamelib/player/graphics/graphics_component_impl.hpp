#ifndef GAME_PLAYER_GRAPHICS_COMPONENT_HPP
#define GAME_PLAYER_GRAPHICS_COMPONENT_HPP

#include <animation.hpp>
#include <game_interface.hpp>
#include <player/graphics/graphics_component_interface.hpp>
#include <memory>

class GraphicsComponentImpl : public GraphicsComponentInterface {
public:
    explicit GraphicsComponentImpl(std::shared_ptr<jt::GameInterface> gameInterface);

    void updateGraphics(float elapsed) override;
    void setPosition(jt::Vector2f const& playerPosition) override;
    void setRotation(float angle);
    void draw(std::shared_ptr<jt::RenderTargetInterface> target) override;
    void flash(float time, jt::Color const& color) override;

private:
    void createAnimation(jt::TextureManagerInterface& textureManager);
    std::shared_ptr<jt::Sprite> m_sprite;
};

#endif // GAME_PLAYER_GRAPHICS_COMPONENT_HPP
