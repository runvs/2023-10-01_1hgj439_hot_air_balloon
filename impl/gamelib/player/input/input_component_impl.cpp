#include "input_component_impl.hpp"
#include <game_properties.hpp>

InputComponentImpl::InputComponentImpl(std::shared_ptr<jt::KeyboardInterface> keyboardInterface)
    : m_keyboard { keyboardInterface }
{
}

void InputComponentImpl::updateMovement(InputTargetInterface& target)
{
    target.setVelocity(jt::Vector2f { 0.0f, 0.0f });

    auto const speed = 100.0f;

    if (m_keyboard->pressed(jt::KeyCode::D) || m_keyboard->pressed(jt::KeyCode::Right)) {
        target.addVelocity(jt::Vector2f { speed, 0.0f });
    }
    if (m_keyboard->pressed(jt::KeyCode::A) || m_keyboard->pressed(jt::KeyCode::Left)) {
        target.addVelocity(jt::Vector2f { -speed, 0.0f });
    }
    auto pos = target.getPosition();
    if (pos.x <= 0) {
        pos.x = 0;
    }
    if (pos.x >= GP::GetScreenSize().x - 32) {
        pos.x = GP::GetScreenSize().x - 32;
    }
    target.setPosition(pos);
}
