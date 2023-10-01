#include "game_properties.hpp"
#include <color/palette_builder.hpp>

namespace {

jt::Palette createPalette()
{
    jt::PaletteBuilder builder;
    return builder
        .addColorsFromGPL(R"(GIMP Palette
#Palette Name: Manon
255 0 128 ff0080
255 255 255 ffffff
136 253 246 88fdf6
10 124 255 0a7cff
0 0 128 000080
0 0 0 000000)")
        .create();
}

} // namespace

jt::Palette GP::getPalette()
{
    static auto const p = createPalette();
    return p;
}

int GP::PhysicVelocityIterations() { return 20; }

int GP::PhysicPositionIterations() { return 20; }
jt::Vector2f GP::PlayerSize() { return jt::Vector2f { 32, 32 }; }
float GP::CloudMoveSpeed() { return 20.0f; }
