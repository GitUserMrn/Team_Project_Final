// Created by David on 5/20/2023.

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <random>

#include "Headers/Player.hpp"
#include "Headers/Global.hpp"
#include "Headers/Bullet.hpp"
#include "Headers/Enemy.hpp"
#include "Headers/BonusEnemy.hpp"
#include "Headers/Score.hpp"

Player::Player(bool isPlayer2, Score& score) : Entity(), player_score(score), explosion(EXPLOSION_ANIMATION_SPEED, BASE_SIZE,
                                                     R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Explosion.png)") {
    reset();


    this->isPlayer2 = isPlayer2;

    current_power = 0;
    reload_timer = 0;

    if (this->checkP2()) {
        // load player2 texture
        texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Test-Player.png)");
    } else {
        // load player1 texture
        texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Test-Player2.png)");
    }

    bullet_texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Player-Bullet.png)");

    sprite.setTexture(texture);
    bullet_sprite.setTexture(bullet_texture);
}

void Player::reset() {
    current_power = 0;
    reload_timer = 0;
    dead_animation_over = false;
    shield_animation_over = true;
    power_timer = 0;

    if (isPlayer2) {
        isPlayer2 = true;
    }

    if (this->checkP2()) {
        // load player2 texture
        texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Test-Player.png)");
    } else {
        // load player1 texture
        texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Test-Player2.png)");
    }



    dead = false;
    x = 0.5f * (SCREEN_WIDTH - BASE_SIZE);
    y = SCREEN_HEIGHT - 2 * BASE_SIZE;

    player_bullets.clear();

    explosion.reset();
}

void Player::update(std::mt19937_64& random_engine,
                    std::vector<Bullet>& enemy_bullets,
                    std::vector<Enemy>& enemies,
                    BonusEnemy& bonus_enemy,
                    bool isPlayer2) {
    if (!dead) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 5);

        if (isPlayer2) {
            // controls for player2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                current_power = 0;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                current_power = 1;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                current_power = 2;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                current_power = 3;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
                current_power = 4;
                power_timer = POWERUP_DURATION;
            }

            // move left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (current_power == 1) {
                    x = std::min<float>(PLAYER_MOVE_SPEED + x, SCREEN_WIDTH - 2 * BASE_SIZE);
                } else {
                    x = std::max<float>(x - PLAYER_MOVE_SPEED, BASE_SIZE);
                }
            }

            // move right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (current_power == 1) {
                    x = std::max<float>(x - PLAYER_MOVE_SPEED, BASE_SIZE);
                } else {
                    x = std::min<float>(PLAYER_MOVE_SPEED + x, SCREEN_WIDTH - 2 * BASE_SIZE);
                }
            }

            // player shoot
            if (reload_timer == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (current_power == 2) {
                    reload_timer = FAST_RELOAD_DURATION;
                } else {
                    reload_timer = RELOAD_DURATION;
                }

                player_bullets.push_back(Bullet(0, -PLAYER_BULLET_SPEED, x, y));
                if (current_power == 3) {
                    player_bullets.push_back(Bullet(0, -PLAYER_BULLET_SPEED, x - 0.375f * BASE_SIZE, y));
                    player_bullets.push_back(Bullet(0, -PLAYER_BULLET_SPEED, x + 0.375f * BASE_SIZE, y));
                }
            } else {
                reload_timer--;
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                current_power = 0;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                current_power = 1;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                current_power = 2;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                current_power = 3;
                power_timer = POWERUP_DURATION;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                current_power = 4;
                power_timer = POWERUP_DURATION;
            }

            // move left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (current_power == 1) {
                    x = std::min<float>(PLAYER_MOVE_SPEED + x, SCREEN_WIDTH - 2 * BASE_SIZE);
                } else {
                    x = std::max<float>(x - PLAYER_MOVE_SPEED, BASE_SIZE);
                }
            }

            // move right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (current_power == 1) {
                    x = std::max<float>(x - PLAYER_MOVE_SPEED, BASE_SIZE);
                } else {
                    x = std::min<float>(PLAYER_MOVE_SPEED + x, SCREEN_WIDTH - 2 * BASE_SIZE);
                }
            }

            // player shoot
            if (reload_timer == 0) {
                if ((current_power != 1) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))) {
                    if (current_power == 2) {
                        reload_timer = FAST_RELOAD_DURATION;
                    } else {
                        reload_timer = RELOAD_DURATION;
                    }

                    player_bullets.push_back(Bullet(0, -PLAYER_BULLET_SPEED, x, y));

                    if (current_power == 3) {
                        player_bullets.push_back(Bullet(0, -PLAYER_BULLET_SPEED, x - 0.375f * BASE_SIZE, y));
                        player_bullets.push_back(Bullet(0, -PLAYER_BULLET_SPEED, x + 0.375f * BASE_SIZE, y));
                    }

                    player_score.increaseShotsFired();

                } else if ((current_power == 1) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
                    reload_timer = RELOAD_DURATION;
                    player_bullets.push_back(Bullet(0, -PLAYER_BULLET_SPEED, x, y));
                    player_score.increaseShotsFired();
                }



            } else {
                reload_timer--;
            }
        }
//


        for (Bullet& bullet : enemy_bullets) {
            if (get_hitbox().intersects(bullet.get_hitbox())) {
                if (current_power == 4) {
                    current_power = 0;
                    shield_animation_over = false;
                } else {
                    dead = true;
                }

                bullet.dead = true;
                break;
            }
        }

        if (bonus_enemy.check_powerup_collision(get_hitbox())) {
            current_power = dis(gen);
            power_timer = POWERUP_DURATION;
            player_score.increasePowerupsTaken();
        }

        if (current_power > 0) {
            if (power_timer == 0) {
                current_power = 0;
            } else {
                power_timer--;
            }
        }

        if (!shield_animation_over) {
            shield_animation_over = explosion.update();
        }
    } else if (!dead_animation_over) {
        dead_animation_over = explosion.update();
    }

    for (Bullet& bullet : player_bullets) {
        bullet.update();

        if (!bullet.dead) {
            if (bonus_enemy.check_bullet_collision(random_engine, bullet.get_hitbox())) {
                bullet.dead = true;
                player_score.increaseEnemiesShot();
            }
        }
    }

    for (Enemy& enemy : enemies) {
        for (Bullet& bullet : player_bullets) {
            if ((!bullet.dead) && (0 < enemy.get_health()) && enemy.get_hitbox().intersects(bullet.get_hitbox())) {
                bullet.dead = true;
                enemy.hit();
                player_score.increaseEnemiesShot();
                break;
            }
        }
    }

    player_bullets.erase(
            std::remove_if(player_bullets.begin(), player_bullets.end(), [](const Bullet& bullet) {
                return bullet.dead;
            }), player_bullets.end());
}

void Player::draw(sf::RenderWindow& window) {
    if (!dead) {
        sprite.setTextureRect(sf::IntRect(BASE_SIZE * current_power, 0, BASE_SIZE, BASE_SIZE));
        sprite.setPosition(sf::Vector2f(x, y));

        for (const Bullet& bullet : player_bullets) {
            bullet_sprite.setPosition(bullet.x, bullet.y);
            window.draw(bullet_sprite);
        }

        window.draw(sprite);

        if (!shield_animation_over) {
            explosion.draw(x, y, window, sf::Color(0, 109, 255));
        }
    } else if (!dead_animation_over) {
        explosion.draw(x, y, window, sf::Color(255, 36, 0));
    }
}

sf::IntRect Player::get_hitbox() const {
    return sf::IntRect(
            static_cast<int>(x + 0.125f * BASE_SIZE),
            static_cast<int>(y + 0.125f * BASE_SIZE),
            static_cast<int>(0.75f * BASE_SIZE),
            static_cast<int>(0.75f * BASE_SIZE)
    );
}

void Player::die() {
    dead = true;
}

bool Player::get_dead_animation_over() const {
    return dead_animation_over;
}

unsigned short Player::get_power_timer() const {
    return power_timer;
}

unsigned char Player::get_current_power() const {
    return current_power;
}

bool Player::checkP2() const{
    return isPlayer2;
};

void Player::enableP2(){
    this->isPlayer2 = true;
};

void Player::disableP2(){
    this->isPlayer2 = false;
};