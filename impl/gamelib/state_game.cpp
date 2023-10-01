#include "state_game.hpp"
#include "random/random.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <math_helper.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <state_menu.hpp>

void StateGame::onCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_clouds = std::make_shared<jt::ObjectGroup<Cloud>>();
    add(m_clouds);
    createPlayer();

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    m_timerText = jt::dh::createText(renderTarget(), "Timer: 0.00 s", 16);
    m_timerText->setTextAlign(jt::Text::TextAlign::LEFT);
    addCloud(jt::Vector2f { 100, 100 });

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::onEnter() { }

void StateGame::createPlayer()
{
    m_player = std::make_shared<Player>(m_world);
    add(m_player);
}

void StateGame::onUpdate(float const elapsed)
{
    if (m_running) {
        m_scoreTimer += elapsed;
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here

        if (getGame()->input().keyboard()->pressed(jt::KeyCode::LShift)
            && getGame()->input().keyboard()->pressed(jt::KeyCode::Escape)) {
            endGame();
        }

        m_cloudSpawnTimer -= elapsed;
        if (m_cloudSpawnTimer <= 0) {
            m_cloudSpawnTimer = m_cloudSpawnTimerMax;
            addCloud(jt::Random::getRandomPointIn(jt::Rectf { 0, -100, GP::GetScreenSize().x, 2 }));
            m_cloudSpawnTimerMax -= 0.1f;
            if (m_cloudSpawnTimerMax <= 0.01f) {
                m_cloudSpawnTimerMax = 0.01f;
            }

            if (m_scoreTimer >= 20.0f) {
                addCloud(m_player->getPosition()
                    + jt::Vector2f { 0.0f, GP::GetScreenSize().y / 2 + 20.0f });
            }
        }

        m_speedUpgradeTimer -= elapsed;
        if (m_speedUpgradeTimer <= 0.0f) {
            m_cloudMoveSpeedFactor *= 1.04f;
            m_speedUpgradeTimer = 3.0f;
        }

        auto const playerPos = m_player->getPosition();
        //        std::cout << playerPos << std::endl;
        for (auto& cloud : *m_clouds) {
            auto c = cloud.lock();
            auto pos = c->getPosition();

            auto const dir = playerPos - pos;
            auto const dist = jt::MathHelper::length(dir);

            if (dist <= 16 + 7) {
                endGame();
            }

            pos += jt::Vector2f { 0, GP::CloudMoveSpeed() * m_cloudMoveSpeedFactor * elapsed };
            c->setPosition(pos);
            if (pos.y >= GP::GetScreenSize().y + 100) {
                c->kill();
            }
        }
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
    m_timerText->setText(
        "Timer: " + jt::MathHelper::floatToStringWithXDigits(m_scoreTimer, 1) + " s");
    m_timerText->update(elapsed);
}

void StateGame::onDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
    m_timerText->draw(renderTarget());
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    std::ofstream fi { "score.txt" };
    fi << m_scoreTimer << std::endl;
    getGame()->stateManager().switchToStoredState("menu");
}

std::string StateGame::getName() const { return "State Game"; }

void StateGame::addCloud(jt::Vector2f const& pos)
{
    auto cloud = std::make_shared<Cloud>();
    m_clouds->push_back(cloud);
    add(cloud);
    cloud->setPosition(pos);
}
