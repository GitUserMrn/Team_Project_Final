#include <SFML/Graphics/Rect.hpp>
#include "Headers/Global.hpp"
#include "Headers/Powerup.hpp"

Powerup::Powerup(short x, short y, unsigned char powerup_type)
        : dead(0),
          x(x),
          y(y),
          powerup_type(powerup_type) { }

sf::IntRect Powerup::get_hitbox() const {
    return sf::IntRect(x + 0.25f * BASE_SIZE,
                       y + 0.25f * BASE_SIZE,
                       0.5f * BASE_SIZE,
                       0.5f * BASE_SIZE);
}
