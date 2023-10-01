#include "player.hpp"
#include "game_properties.hpp"
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <player/graphics/graphics_component_impl.hpp>
#include <player/input/input_component_impl.hpp>
#include <player/sound/sound_component_impl.hpp>
#include <state_game.hpp>
#include <Box2D/Box2D.h>

namespace {
std::string selectWalkAnimation(jt::Vector2f const& velocity)
{
    std::string walkAnimationName { "idle" };

    if (jt::MathHelper::lengthSquared(velocity) < 2) {
        walkAnimationName = "idle";
    } else if (abs(velocity.x) > abs(velocity.y)) {
        if (velocity.x > 0) {
            walkAnimationName = "right";
        } else {
            walkAnimationName = "left";
        }
    } else {
        if (velocity.y > 0 && abs(velocity.x) < 0.1f) {
            walkAnimationName = "down";
        } else if (velocity.y > 0 && velocity.x > 0) {
            walkAnimationName = "down_right";
        } else if (velocity.y > 0 && velocity.x < 0) {
            walkAnimationName = "down_left";
        } else {
            walkAnimationName = "up";
        }
    }

    return walkAnimationName;
}
} // namespace

Player::Player(std::shared_ptr<jt::Box2DWorldInterface> world)
{
    b2BodyDef def;
    def.type = b2BodyType::b2_dynamicBody;
    m_b2Object = std::make_unique<jt::Box2DObject>(world, &def);
    m_b2Object->setPosition(GP::GetScreenSize() * 0.5f);
}

void Player::doCreate()
{
    m_input = std::make_unique<InputComponentImpl>(getGame()->input().keyboard());
    m_sound = std::make_unique<SoundComponentImpl>(getGame()->audio(), getGame()->logger());
    m_graphics = std::make_unique<GraphicsComponentImpl>(getGame());
}

void Player::doUpdate(float const elapsed)
{

    m_graphics->setRotation(m_angle);

    m_input->updateMovement(*m_b2Object);

    float angleIncrement = 35.0f;
    float const maxAngle = 50;
    if (m_b2Object->getVelocity().x < 0) {
        m_angle += angleIncrement * elapsed;
        if (m_angle <= 0) {
            m_angle += angleIncrement * elapsed;
        }
        if (m_angle >= maxAngle) {
            m_angle = maxAngle;
        }
    } else if (m_b2Object->getVelocity().x > 0) {
        m_angle -= angleIncrement * elapsed;
        if (m_angle >= 0) {
            m_angle -= angleIncrement * elapsed;
        }
        if (m_angle <= -maxAngle) {
            m_angle = -maxAngle;
        }
    } else {
        m_angle *= 0.99f;
    }
    //    std::cout << m_angle << std::endl;
    m_graphics->setPosition(m_b2Object->getPosition());
    m_graphics->updateGraphics(elapsed);
}
void Player::doDraw() const { m_graphics->draw(renderTarget()); }
jt::Vector2f Player::getPosition() const { return m_b2Object->getPosition(); }
