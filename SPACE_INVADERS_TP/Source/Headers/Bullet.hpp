#ifndef PP_SPACE_INVASION_BULLET_HPP
#define PP_SPACE_INVASION_BULLET_HPP

#endif //PP_SPACE_INVASION_BULLET_HPP


#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <array>

struct Bullet {

    bool dead; // the bullet, not the player :))

    // current coord of the bullet
    float real_x;
    float real_y;

    // amount by which the bullet's coord change in each update step
    float step_x;
    float step_y;

    // current coord of the bullet rounded to the nearest integer
    short x;
    short y;

    // the previous coord of the bullet for the trail effect
    std::array<short, 3> previous_x;
    std::array<short, 3> previous_y;

    Bullet(float i_step_x, float i_step_y, short i_x, short i_y);

    void update();

    sf::IntRect get_hitbox() const;
};

#endif
