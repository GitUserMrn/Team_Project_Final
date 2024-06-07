#ifndef PP_SPACE_INVASION_POWERUP_HPP
#define PP_SPACE_INVASION_POWERUP_HPP



#include <SFML/Graphics/Rect.hpp>

struct Powerup {

    bool dead;
    short x;
    short y;

    //1 - mirrored controls
    //2 - fast reload
    //3 - shotgun bullets
    //4 - shield
    unsigned char powerup_type;

    Powerup(short x, short y, unsigned char powerup_type);

    sf::IntRect get_hitbox() const;
};

#endif
