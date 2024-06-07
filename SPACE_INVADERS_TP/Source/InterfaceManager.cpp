#include <SFML/Graphics.hpp>

#include "Headers/InterfaceManager.hpp"

void draw_text(short i_x, short i_y, const std::string& i_text, sf::RenderWindow& i_window, const sf::Texture& i_font_texture)
{
    short character_x = i_x;
    short character_y = i_y;

    unsigned char character_height = i_font_texture.getSize().y;
    //There are 96 characters in the font texture.
    unsigned char character_width = i_font_texture.getSize().x / 96;

    sf::Sprite character_sprite(i_font_texture);

    for (std::string::const_iterator a = i_text.begin(); a != i_text.end(); a++)
    {
        if ('\n' == *a)
        {
            character_x = i_x;
            character_y += character_height;

            continue;
        }

        character_sprite.setPosition(character_x, character_y);
        character_sprite.setTextureRect(sf::IntRect(character_width * (*a - 32), 0, character_width, character_height));

        character_x += character_width;

        i_window.draw(character_sprite);
    }
}

void draw_text_centered(float x, float y, const std::string& text, sf::RenderWindow& window, const sf::Texture& font_texture)
{
    float text_width = text.length() * (font_texture.getSize().x / 96.0f);
    float text_height = font_texture.getSize().y;

    sf::Sprite character_sprite(font_texture);

    float text_x = x - text_width / 2.0f;
    float text_y = y - text_height / 2.0f;

    for (const char& c : text) {
        if (c == '\n') {
            text_x = x - text_width / 2.0f;
            text_y += text_height;
            continue;
        }

        character_sprite.setPosition(text_x, text_y);
        character_sprite.setTextureRect(sf::IntRect((c - 32) * (font_texture.getSize().x / 96), 0, font_texture.getSize().x / 96, font_texture.getSize().y));

        text_x += font_texture.getSize().x / 96.0f;

        window.draw(character_sprite);
    }
}