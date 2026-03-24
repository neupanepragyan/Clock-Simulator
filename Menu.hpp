#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu {
private:
    int selectedIndex = 0;
    sf::Text options[2];
public:
    Menu(float width, float height, const sf::Font& font) 
        : options{sf::Text(font), sf::Text(font)} 
    {
        options[0].setString("1. Sync with System Clock");
        options[0].setCharacterSize(28);
        options[0].setFillColor(sf::Color::Red);
        options[0].setPosition({width / 2.0f - 160.f, height / 2.0f - 60.f});

        options[1].setString("2. Set Custom Starting Time");
        options[1].setCharacterSize(28);
        options[1].setFillColor(sf::Color::Black);
        options[1].setPosition({width / 2.0f - 160.f, height / 2.0f + 10.f});
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& opt : options) window.draw(opt);
    }

    void moveUp() {
        selectedIndex = 0;
        options[0].setFillColor(sf::Color::Red);
        options[1].setFillColor(sf::Color::Black);
    }

    void moveDown() {
        selectedIndex = 1;
        options[0].setFillColor(sf::Color::Black);
        options[1].setFillColor(sf::Color::Red);
    }

    int getPressedItem() const { return selectedIndex; }
};
#endif