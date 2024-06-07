#pragma once

#ifndef PP_SPACE_INVASION_ENTITY_HPP
#define PP_SPACE_INVASION_ENTITY_HPP




#include <SFML/Graphics.hpp>
#include <vector>
#include <random>



class Entity {

protected:
    bool dead{};

    unsigned short x{};
    unsigned short y{};

    sf::Texture texture;

public:
    Entity();

    bool get_dead() const;
    unsigned short get_x() const;
    unsigned short get_y() const;

    // these virtual methods will need to be implemented in the child classes
    virtual sf::IntRect get_hitbox() const = 0;


    sf::Sprite sprite;
};

#endif