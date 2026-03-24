#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <ctime>
#include <iostream>
#include "Menu.hpp"
#include "Line.hpp"
#include "Circle.hpp"

const float PI = 3.14159265f;

sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f center, float angleDegrees) {
    float radians = angleDegrees * (PI / 180.f);
    float s = sin(radians);
    float c = cos(radians);

    //Translation to Origin
    float x = point.x - center.x;
    float y = point.y - center.y;

    //Rotation
    return {
        x * c - y * s + center.x,
        x * s + y * c + center.y
    };
}

int main() {
    //Main window definition
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Manual Mechanical Clock - 081BCT049");
    window.setFramerateLimit(60);

    //Defining font for menu
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) return -1;

    //Option Menu Definition
    Menu menu(600, 600, font);
    enum { MENU, RUN } state = MENU;

    //Center of clock
    sf::Vector2f center(300, 300);

    //Clock face definition
    Circle outer_circle(300, 300, 250, sf::Color::Black);
    Circle inner_circle(300, 300, 251, sf::Color::Red);
    outer_circle.draw_algorithm();
    inner_circle.draw_algorithm();

    //Time keeping variables definition
    int h = 0, m = 0, s = 0;
    bool useSystem = true;
    sf::Clock internalTimer;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            //Draw and navigate menu if on MENU state. 
            if (state == MENU && event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;
                if (key == sf::Keyboard::Key::Up) menu.moveUp();
                if (key == sf::Keyboard::Key::Down) menu.moveDown();
                if (key == sf::Keyboard::Key::Enter) {
                    if (menu.getPressedItem() == 1) {
                        std::cout << "Enter Time (HH MM SS): ";
                        std::cin >> h >> m >> s;
                        useSystem = false;
                    }
                    state = RUN;
                }
            }
        }

        window.clear(sf::Color::White);

        if (state == MENU) {
            menu.draw(window);
        } else {
            if (useSystem) {
                std::time_t now = std::time(nullptr);
                std::tm* t = std::localtime(&now);
                h = t->tm_hour; m = t->tm_min; s = t->tm_sec;
            } else if (internalTimer.getElapsedTime().asSeconds() >= 1.f) {
                s++; 
                if(s>=60){s=0; m++;} 
                if(m>=60){m=0; h++;}
                internalTimer.restart();
            }

            //Circular watch face rendering
            outer_circle.render(window);
            inner_circle.render(window);
            
            //Hour Markers
            for (int i = 0; i < 12; i++) {
                sf::Vector2f p1 = rotatePoint({300, 70}, center, i * 30.f);
                sf::Vector2f p2 = rotatePoint({300, 50}, center, i * 30.f);
                Line temp(p1.x, p1.y, p2.x, p2.y, sf::Color::Black);
                temp.draw_algorithm();
                temp.render(window);
            }

            //Transforming hand endpoints to change time
            float sAngle = s * 6.f;
            float mAngle = m * 6.f + s * 0.1f;
            float hAngle = (h % 12) * 30.f + m * 0.5f;
            sf::Vector2f sTip = rotatePoint({300, 80}, center, sAngle);
            sf::Vector2f mTip = rotatePoint({300, 110}, center, mAngle);
            sf::Vector2f hTip = rotatePoint({300, 160}, center, hAngle);

            //Drawing updated hand postion.
            Line secondHand(center.x, center.y, sTip.x, sTip.y, sf::Color::Red);
            secondHand.draw_algorithm();
            secondHand.render(window);
            Line minuteHand(center.x, center.y, mTip.x, mTip.y, sf::Color::Black);
            minuteHand.draw_algorithm();
            minuteHand.render(window);
            Line hourHand(center.x, center.y, hTip.x, hTip.y, sf::Color::Green);
            hourHand.draw_algorithm();
            hourHand.render(window);
        }
        window.display();
    }
    return 0;
}

//g++ -std=c++20 main.cpp -o clock_simulation -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./clock_simulation