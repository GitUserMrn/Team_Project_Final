#include "Entity.hpp"
#include "AnimationManager.hpp"
#include "Powerup.hpp"

#ifndef PP_SPACE_INVASION_BONUSENEMY_HPP
#define PP_SPACE_INVASION_BONUSENEMY_HPP

class BonusEnemy: public Entity {

protected:
    bool dead;
    bool dead_animation_over;

    short explosion_x;

    unsigned short timer;

    std::uniform_int_distribution<unsigned short> powerup_distrib;

    std::uniform_int_distribution<unsigned short> timer_distrib;

    std::vector<AnimationManager> powerup_animations;

    std::vector<Powerup> powerups;

    AnimationManager animation;
    AnimationManager explosion;
public:
    explicit BonusEnemy(std::mt19937_64& random_engine);

    bool check_bullet_collision(std::mt19937_64& random_engine, const sf::IntRect& bullet_hitbox);

    bool check_powerup_collision(const sf::IntRect& player_hitbox);

    void draw(sf::RenderWindow& window);
    void reset(bool dead, std::mt19937_64& random_engine);
    void update(std::mt19937_64& random_engine);

    sf::IntRect get_hitbox() const;

    const unsigned char y;
};


#endif //PP_SPACE_INVASION_BONUSENEMY_HPP
