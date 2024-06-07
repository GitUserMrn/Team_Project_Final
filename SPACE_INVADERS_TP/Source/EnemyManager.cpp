#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>


#include "Headers/Global.hpp"
#include "Headers/Enemy.hpp"
#include "Headers/EnemyManager.hpp"


EnemyManager::EnemyManager(): shoot_distrib(0, ENEMY_SHOOT_CHANCE) {

    reset(0);

    this->enemy_bullet_texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Enemy-Bullet-1.png)");
    this->enemy_bullet_sprite.setTexture(enemy_bullet_texture);

    std::string path = R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources/Images/Enemy-1.png)";

    for (unsigned char a = 0; a < 3; a++) {
        enemy_animations.push_back(AnimationManager(1 + pause, BASE_SIZE, R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Enemy-)" + std::to_string(static_cast<unsigned short>(a)) + ".png"));
    }
}

bool EnemyManager::reached_player(unsigned short player_y) const {
    for (const Enemy& enemy: enemies) {
        if (enemy.get_y() > player_y - 0.5f * BASE_SIZE) {
            // we will make this end the game
            return true;
        }
    }
    return false;
}

void EnemyManager::draw(sf::RenderWindow& window) {

    for (const Bullet& bullet : this->enemy_bullets) {

        for (unsigned char i=0; i < bullet.previous_x.size(); i++) {

            enemy_bullet_sprite.setPosition(bullet.previous_x[i], bullet.previous_y[i]);
            enemy_bullet_sprite.setTextureRect(sf::IntRect(BASE_SIZE * i, 0, BASE_SIZE, BASE_SIZE));

            window.draw(enemy_bullet_sprite);

        }

        enemy_bullet_sprite.setPosition(bullet.x, bullet.y);
        enemy_bullet_sprite.setTextureRect(sf::IntRect(BASE_SIZE * bullet.previous_x.size(), 0, BASE_SIZE, BASE_SIZE));

        window.draw(enemy_bullet_sprite);
    }

    for (const Enemy& enemy : enemies) {

        if (enemy.alive) {


            sf::Color enemy_color = sf::Color(255, 255, 255);
            if (enemy.get_hit_timer()) {
                enemy_color = sf::Color(255, 255, 255);
            }
            enemy_animations[enemy.get_enemy_type()].draw(enemy.get_x(), enemy.get_y(), window, enemy_color);
        }
    }

}


void EnemyManager::reset(unsigned short wave) {
    unsigned char enemy_x = 0;
    unsigned char enemy_y = 0;

    std::string level_sketch;

    pause = std::max<short>(ENEMY_MOVE_PAUSE_START_MIN, ENEMY_MOVE_PAUSE_START - ENEMY_MOVE_PAUSE_DECREASE * wave);
    move_timer = pause;

    shoot_distrib = std::uniform_int_distribution<unsigned short>(0, std::max<short>(ENEMY_SHOOT_CHANCE_MIN, ENEMY_SHOOT_CHANCE - ENEMY_SHOOT_CHANCE_INCREASE * wave));

    for (AnimationManager& enemy_animation : enemy_animations) {
        enemy_animation.reset();
    }

    enemy_bullets.clear();

    enemies.clear();

    if (TOTAL_WAVES <= wave) {
        wave = 0.5f * TOTAL_WAVES + wave % static_cast<unsigned char>(0.5f * TOTAL_WAVES);
    }

    switch (wave) {
        case 0:
        {
            level_sketch = "0 1 0 1 0 1 0 1 \n 2 0 2 1 2 0 2 1\n1 2 2 1 2 2 1 2 \n 1 0 2 0 1 0 2 0";

            break;
        }
        case 1:
        {
            level_sketch = "1201021212101012\n2120101210122102\n012012010210210\n1201201201201201";

            break;
        }
        case 2:
        {
            //OH MY GOD, IS THAT A CHECKBOARD PATTERN?!
            level_sketch = "  02020000202  \n 12210011001221 \n1212120002121212\n 12121200212121 ";

            break;
        }
        case 3:
        {
            level_sketch = "   1111111111   \n1111111111111111\n1111111111111111\n1111111111111111";

            break;
        }
        case 4:
        {

            level_sketch = "2222222222222222\n1111111111111111\n1010101010101010\n0101010101010101";

            break;
        }
        case 5:
        {

            level_sketch = "0000000000000000\n2222222222222222\n1111111111111111\n1111111111111111";

            break;
        }
        case 6:
        {
            //CHECKBOARD PATTERN AGAIN?!
            level_sketch = "2121212121212121\n1212121212121212\n2121212121212121\n1212121212121212";

            break;
        }
        case 7:
        {
            level_sketch = "2222222222222222\n2222222222222222\n2222222222222222\n2222222222222222";
        }
    }


    for (char sketch_character : level_sketch) {
        enemy_x++;

        switch (sketch_character) {

            case '\n': {
                enemy_x = 0;
                enemy_y++;
                break;

            } case '0': {
                enemies.emplace_back(0, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y));

                break;
            } case '1': {
                enemies.emplace_back(1, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y));

                break;
            } case '2': {
                enemies.emplace_back(2, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y));
            }
        }
    }
}

// to check if a bullet is dead
bool isBulletDead(const Bullet& bullet) {
    return bullet.dead;
}

// to remove dead bullets from the vector
void removeDeadBullets(std::vector<Bullet>& enemy_bullets) {
    enemy_bullets.erase(std::remove_if(enemy_bullets.begin(), enemy_bullets.end(), isBulletDead), enemy_bullets.end());
}

// to check if an enemy is not alive
bool isEnemyNotAlive(const Enemy& enemy) {
    return !enemy.alive;
}

// to update the enemy manager
void EnemyManager::update(std::mt19937_64& random_engine) {
    std::vector<Enemy>::iterator dead_enemies_start;

    if (move_timer == 0) {
        move_timer = pause;

        for (Enemy& enemy : enemies) {
            enemy.move();
        }

        for (AnimationManager& enemy_animation : enemy_animations) {
            enemy_animation.change_curr_frame();
        }

    } else {
        move_timer--;
    }

    for (Enemy& enemy : enemies) {
        enemy.update();

        if (shoot_distrib(random_engine) < 2) {
            enemy.shoot(enemy_bullets);
        }
    }

    dead_enemies_start = std::remove_if(enemies.begin(), enemies.end(), isEnemyNotAlive);

    pause = std::max<int>(ENEMY_MOVE_PAUSE_MIN, pause - ENEMY_MOVE_PAUSE_DECREASE * (enemies.end() - dead_enemies_start));

    enemies.erase(dead_enemies_start, enemies.end());


    for (Bullet& enemy_bullet : enemy_bullets) {
        enemy_bullet.update();
    }

    removeDeadBullets(enemy_bullets);
}


std::vector<Bullet>& EnemyManager::get_enemy_bullets() {
    return enemy_bullets;
}

std::vector<Enemy>& EnemyManager::get_enemies() {
    return enemies;
}
