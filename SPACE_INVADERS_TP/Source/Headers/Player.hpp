#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "AnimationManager.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "BonusEnemy.hpp"
#include "Score.hpp"

#ifndef PP_SPACE_INVASION_PLAYER_HPP
#define PP_SPACE_INVASION_PLAYER_HPP

class Player : public Entity {
private:


    bool dead;
    bool dead_animation_over;
    bool shield_animation_over;

    bool isPlayer2;

    unsigned char current_power;
    unsigned char reload_timer;
    unsigned short power_timer;

    sf::Sprite bullet_sprite;
    sf::Texture bullet_texture;

    std::vector<Bullet> player_bullets;

    AnimationManager explosion;

public:
    Player(bool isPlayer2, Score& score);

    void reset();
    void die();

    sf::IntRect get_hitbox() const override; // will be used for collision detection

    void draw(sf::RenderWindow& window);

    void update(std::mt19937_64& random_engine,
                std::vector<Bullet>& enemy_bullets,
                std::vector<Enemy>& enemies,
                BonusEnemy& bonus_enemy,
                bool isPlayer2);

    bool get_dead_animation_over() const;

    unsigned char get_current_power() const;

    unsigned short get_power_timer() const;

    bool checkP2() const;

    void disableP2();

    void enableP2();

    Score& player_score;
};

#endif