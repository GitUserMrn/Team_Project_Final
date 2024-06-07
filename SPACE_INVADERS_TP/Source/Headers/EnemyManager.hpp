#pragma once


#ifndef PP_SPACE_INVASION_ENEMYMANAGER_HPP
#define PP_SPACE_INVASION_ENEMYMANAGER_HPP


#include <random>
#include <SFML/Graphics/Sprite.hpp>
#include "Enemy.hpp"
#include "AnimationManager.hpp"

class EnemyManager {

private:
    unsigned short move_timer;
    unsigned short pause;


    std::uniform_int_distribution<unsigned short> shoot_distrib;

    std::vector<AnimationManager> enemy_animations;

    std::vector<Enemy> enemies;

    std::vector<Bullet> enemy_bullets;

    sf::Sprite enemy_bullet_sprite;
    sf::Texture enemy_bullet_texture;

public:
    EnemyManager();

    bool reached_player(unsigned short i_player_y) const;

    void draw(sf::RenderWindow& window);

    void update(std::mt19937_64& random_engine);

    std::vector<Bullet>& get_enemy_bullets();

    std::vector<Enemy>& get_enemies();

    void reset(unsigned short level);

};

#endif


