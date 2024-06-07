#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#ifndef PP_SPACE_INVASION_INTERFACEMANAGER_HPP
#define PP_SPACE_INVASION_INTERFACEMANAGER_HPP

void draw_text(short i_x, short i_y, const std::string& i_text, sf::RenderWindow& i_window, const sf::Texture& i_font_texture);


void draw_text_centered(float x, float y, const std::string& text, sf::RenderWindow& window, const sf::Texture& font_texture);
#endif

