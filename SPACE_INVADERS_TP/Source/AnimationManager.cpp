#include <SFML/Graphics.hpp>

#include "Headers/AnimationManager.hpp"

AnimationManager::AnimationManager(unsigned short animation_speed, unsigned short frame_width, const std::string& texture_location) :
        animation_iterator(0),
        animation_speed(std::max<unsigned short>(1, animation_speed)),
        curr_frame(0),
        frame_width(frame_width) {

    texture.loadFromFile(texture_location);
    total_frames = texture.getSize().x / frame_width;
}

//This is for the enemies.
bool AnimationManager::change_curr_frame() {
    curr_frame++;

    if (curr_frame == total_frames) {
        curr_frame = 0;

        return true;
    }

    return false;
}

bool AnimationManager::update() {
    bool output = false;

    animation_iterator++;

    while (animation_iterator >= animation_speed) {
        animation_iterator -= animation_speed;
        curr_frame++;

        if (curr_frame == total_frames) {
            output = true;
            curr_frame = 0;
        }
    }

    return output;
}

void AnimationManager::draw(short x, short y, sf::RenderWindow& window, const sf::Color& color) {
    sprite.setColor(color);
    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(curr_frame * frame_width, 0, frame_width, texture.getSize().y));

    window.draw(sprite);
}

void AnimationManager::reset() {
    animation_iterator = 0;
    curr_frame = 0;
}