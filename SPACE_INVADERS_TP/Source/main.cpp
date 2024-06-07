#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <random>
#include "Headers/Global.hpp"
#include "Headers/Player.hpp"
#include "Headers/EnemyManager.hpp"
#include "Headers/BonusEnemy.hpp"
#include "Headers/InterfaceManager.hpp"
#include "Headers/Score.hpp"

int main() {
    std::chrono::microseconds lag(0);   // to keep track of time between frames
    std::chrono::steady_clock::time_point prev_time;    // used to compute elapsed time between frames

    std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    bool game_over = false;
    bool next_wave = false;

    unsigned short multiplayer_timer = 0;

    unsigned short curr_wave = 0;
    unsigned short waves_survived;
    unsigned short next_wave_timer = NEXT_WAVE_TRANSITION;

    sf::Event event; //input

    sf::RenderWindow window(sf::VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT),
                            "TEST Retro Shooter Game - VERSION 0.5",
                            sf::Style::Close);
    window.setView(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));

    sf::Sprite background_sprite;
    sf::Sprite powerup_bar_sprite;
    sf::Sprite overlay_sprite;

    sf::Texture background_texture;
    sf::Texture font_texture;
    sf::Texture powerup_bar_texture;
    sf::Texture overlay_texture;

    background_texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Background.png)");
    background_sprite.setTexture(background_texture);

    font_texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Font.png)");

    powerup_bar_texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\PowerupBar.png)");
    powerup_bar_sprite.setTexture(powerup_bar_texture);

    // Load the overlay texture and set its transparency
    overlay_texture.loadFromFile(R"(C:\Users\40787\Desktop\PP-SPACE-INVASION\Source\Resources\Overlay.png)");
    overlay_sprite.setTexture(overlay_texture);
    overlay_sprite.setColor(sf::Color(0, 0, 0));

    Score score;

    Player player1(false, score);
    Player player2(false, score);

    EnemyManager enemyManager;

    BonusEnemy bonus_enemy(random_engine);



    prev_time = std::chrono::steady_clock::now();   // the initial value of prev_time

    while (window.isOpen()) {
        std::chrono::microseconds delta_time =
                std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - prev_time);

        lag += delta_time;
        prev_time += delta_time;

        while (FRAME_DURATION <= lag) {
            lag -= FRAME_DURATION;

            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                }
            }

            if (player1.get_dead_animation_over()) {
                game_over = true;

            }

            if (enemyManager.reached_player(player1.get_y())) {
                player1.die();

                if (player2.checkP2()) {
                    player2.die();
                }

            }

            if (!game_over) {
                if (enemyManager.get_enemies().empty()) {
                    if (next_wave_timer == 0) {
                        next_wave = false;

                        curr_wave++;
                        next_wave_timer = NEXT_WAVE_TRANSITION;

                        player1.reset();
                        player2.reset();
                        enemyManager.reset(curr_wave);

                        bonus_enemy.reset(true, random_engine);
                    } else {
                        next_wave = true;

                        next_wave_timer--;
                    }
                } else {
                    player1.update(random_engine, enemyManager.get_enemy_bullets(), enemyManager.get_enemies(), bonus_enemy, false);

                    if (player2.checkP2()) {
                        player2.update(random_engine, enemyManager.get_enemy_bullets(), enemyManager.get_enemies(), bonus_enemy, true);
                    }

                    enemyManager.update(random_engine);
                    bonus_enemy.update(random_engine);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                game_over = false;
                curr_wave = 0;
                player1.reset();
                score.reset();

                if (player2.checkP2()) {
                    player2.reset();
                }

                enemyManager.reset(0);
                bonus_enemy.reset(true, random_engine);
            }
        }

        window.clear();
        window.draw(background_sprite);

        if (!player1.get_dead() || !player2.get_dead()) {
            enemyManager.draw(window);
            bonus_enemy.draw(window);

            if (multiplayer_timer == 0){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                    if (player2.checkP2()) {
                        player2.disableP2();
                        player2.die();
                        multiplayer_timer = MULTYPLAYER_SWITCH_TIMER;

                    } else {
                        player2.enableP2();
                        player2.reset();
                        multiplayer_timer = MULTYPLAYER_SWITCH_TIMER;
                    }


                }
            } else {
                multiplayer_timer--;
            }



            if (player1.get_current_power() > 0) {
                powerup_bar_sprite.setColor(sf::Color(255, 255, 255));
                powerup_bar_sprite.setPosition(SCREEN_WIDTH - powerup_bar_texture.getSize().x - 0.25f * BASE_SIZE, 0.25f * BASE_SIZE);
                powerup_bar_sprite.setTextureRect(sf::IntRect(0, 0, powerup_bar_texture.getSize().x, BASE_SIZE));

                window.draw(powerup_bar_sprite);

                powerup_bar_sprite.setPosition(SCREEN_WIDTH - powerup_bar_texture.getSize().x - 0.125f * BASE_SIZE, 0.25f * BASE_SIZE);
                // computing the length of the bar.
                powerup_bar_sprite.setTextureRect(sf::IntRect(0.125f * BASE_SIZE, BASE_SIZE, ceil(player1.get_power_timer() * static_cast<float>(powerup_bar_texture.getSize().x - 0.25f * BASE_SIZE) / POWERUP_DURATION), BASE_SIZE));

                switch (player1.get_current_power()) {
                    case 1:
                        powerup_bar_sprite.setColor(sf::Color(0, 146, 255));
                        break;
                    case 2:
                        powerup_bar_sprite.setColor(sf::Color(255, 0, 0));
                        break;
                    case 3:
                        powerup_bar_sprite.setColor(sf::Color(255, 219, 0));
                        break;
                    case 4:
                        powerup_bar_sprite.setColor(sf::Color(219, 0, 255));
                        break;
                }

                window.draw(powerup_bar_sprite);
            }

            if (player2.get_current_power() > 0) {
                powerup_bar_sprite.setColor(sf::Color(255, 255, 255));
                powerup_bar_sprite.setPosition(0.01f * BASE_SIZE, 0.01f * BASE_SIZE);
                powerup_bar_sprite.setTextureRect(sf::IntRect(0, 0, powerup_bar_texture.getSize().x, BASE_SIZE));

                window.draw(powerup_bar_sprite);

                powerup_bar_sprite.setPosition(0.375f * BASE_SIZE, 0.75f * BASE_SIZE);
                // computing the length of the bar.
                powerup_bar_sprite.setTextureRect(sf::IntRect(0.125f * BASE_SIZE, BASE_SIZE, ceil(player2.get_power_timer() * static_cast<float>(powerup_bar_texture.getSize().x - 0.25f * BASE_SIZE) / POWERUP_DURATION), BASE_SIZE));

                switch (player2.get_current_power()) {
                    case 1:
                        powerup_bar_sprite.setColor(sf::Color(0, 146, 255));
                        break;
                    case 2:
                        powerup_bar_sprite.setColor(sf::Color(255, 0, 0));
                        break;
                    case 3:
                        powerup_bar_sprite.setColor(sf::Color(255, 219, 0));
                        break;
                    case 4:
                        powerup_bar_sprite.setColor(sf::Color(219, 0, 255));
                        break;
                }

                window.draw(powerup_bar_sprite);
            }

            player1.draw(window);

            if (player2.checkP2()) {
                player2.draw(window);
            }

            draw_text(0.25f * BASE_SIZE, 0.25f * BASE_SIZE,
                      "Wave: " + std::to_string(curr_wave),
                      window,
                      font_texture);

            if (game_over) {
                window.draw(overlay_sprite);

                draw_text(0.5f * (SCREEN_WIDTH - 5 * BASE_SIZE),
                          0.25f * (SCREEN_HEIGHT - BASE_SIZE),
                          "Game over!",
                          window,
                          font_texture);

                std::string scoreDetails = "Waves Survived: " + std::to_string(curr_wave) + "\n";
                scoreDetails += "Powerups Taken: " + std::to_string(score.getPowerupsTaken()) + "\n";
                scoreDetails += "Enemies Killed: " + std::to_string(score.getEnemiesShot()) + "\n";
                scoreDetails += "Shots Fired:    " + std::to_string(score.getShotsFired()) + "\n";
                scoreDetails += "Shoot Accuracy: " + std::to_string(score.getShootAccuracy()) + "%";

                draw_text(0.4f * (SCREEN_WIDTH - 5 * BASE_SIZE),
                          0.4f * (SCREEN_HEIGHT - BASE_SIZE),
                          scoreDetails,
                          window,
                          font_texture);


            } else if (next_wave) {

                window.draw(overlay_sprite);

                draw_text(0.4f * (SCREEN_WIDTH - 5.5f * BASE_SIZE),
                          0.5f * (SCREEN_HEIGHT - BASE_SIZE),
                          "Next wave incoming!",
                          window,
                          font_texture);
            }
        }
        window.display();
    }

    return 0;
}
