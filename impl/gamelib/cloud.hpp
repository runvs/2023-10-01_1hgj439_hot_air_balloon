
#ifndef HOTAIRBALLOON_CLOUD_HPP
#define HOTAIRBALLOON_CLOUD_HPP

#include "game_object.hpp"
#include "sprite.hpp"

class Cloud : public jt::GameObject {
public:
    void setPosition(jt::Vector2f const& p);

    jt::Vector2f getPosition() const;

private:
    std::shared_ptr<jt::Sprite> m_sprite;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // HOTAIRBALLOON_CLOUD_HPP
