#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <random>
#include "Bullet.hpp"
#include "Entity.hpp"

#ifndef PP_SPACE_INVASION_ENEMY_H
#define PP_SPACE_INVASION_ENEMY_H



class Enemy: public Entity {

private:
    char direction; //-1 left, +1 right, 0 down

    unsigned char health;
    bool dead;

    unsigned char enemy_type;
    unsigned char hit_points;
    unsigned char hit_timer;

public:
    Enemy(unsigned char enemy_type, unsigned short x, unsigned short y);

    unsigned char get_hit_points() const;
    unsigned char get_hit_timer() const; //enemy changes color for a bit as a reaction to being hit
    unsigned short get_enemy_type() const;


    void move();
    void hit();
    void shoot(std::vector<Bullet>& enemy_bullets);
    void update();


    sf::IntRect get_hitbox() const override;

    unsigned char get_health() const;

    bool alive;

    unsigned char color_timer;
};

#endif