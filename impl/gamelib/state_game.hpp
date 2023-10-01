#ifndef GAME_STATE_GAME_HPP
#define GAME_STATE_GAME_HPP

#include "text.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <cloud.hpp>
#include <game_state.hpp>
#include <object_group.hpp>
#include <player/player.hpp>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
class Vignette;
} // namespace jt

class Hud;

class StateGame : public jt::GameState {
public:
    std::string getName() const override;

    void addCloud(jt::Vector2f const& pos);

private:
    std::shared_ptr<jt::Shape> m_background;
    std::shared_ptr<jt::Vignette> m_vignette;
    std::shared_ptr<Hud> m_hud;
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };
    std::shared_ptr<Player> m_player { nullptr };

    std::shared_ptr<jt::ObjectGroup<Cloud>> m_clouds;

    std::shared_ptr<jt::Text> m_timerText;

    float m_scoreTimer = 0.0f;
    float m_speedUpgradeTimer = 3.0f;
    float m_cloudSpawnTimer = 0.0f;
    float m_cloudSpawnTimerMax = 3.0f;

    float m_cloudMoveSpeedFactor = 1.0f;

    bool m_running { true };
    bool m_hasEnded { false };

    int m_scoreP1 { 0 };
    int m_scoreP2 { 0 };

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const elapsed) override;
    void onDraw() const override;

    void endGame();
    void createPlayer();
};

#endif
