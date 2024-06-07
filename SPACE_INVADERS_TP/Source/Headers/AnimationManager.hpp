#pragma once

#ifndef PP_SPACE_INVASION_ANIMATIONMANAGER_HPP
#define PP_SPACE_INVASION_ANIMATIONMANAGER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class AnimationManager {
    unsigned short animation_iterator;
    unsigned short animation_speed;
    unsigned short curr_frame;
    unsigned short frame_width;
    unsigned short total_frames;

    sf::Sprite sprite;

    sf::Texture texture;
public:
    AnimationManager(unsigned short animation_speed, unsigned short frame_width, const std::string& texture_location);

    bool change_curr_frame();
    bool update();

    void draw(short x, short y, sf::RenderWindow& window, const sf::Color& color = sf::Color(255, 255, 255));
    void reset();
};



#endif //PP_SPACE_INVASION_ANIMATIONMANAGER_HPP
