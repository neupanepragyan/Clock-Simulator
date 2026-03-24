#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

class Circle {
private:
    int x_c;
    int y_c;
    int r;
    sf::Color color;
public:
    std::vector<std::pair<int, int>> points;

    Circle(int x_, int y_, int r_, sf::Color color_) {
        x_c = x_;
        y_c = y_;
        r = r_;
        color = color_;
    }

    void add_points(int x_, int y_) {
        points.push_back({x_c + x_, y_c + y_});
        points.push_back({x_c + y_, y_c + x_});
        points.push_back({x_c - x_, y_c + y_});
        points.push_back({x_c - y_, y_c + x_});
        points.push_back({x_c - x_, y_c - y_});
        points.push_back({x_c - y_, y_c - x_});
        points.push_back({x_c + x_, y_c - y_});
        points.push_back({x_c + y_, y_c - x_});
    }

    void draw_algorithm() { 
        points.clear(); 
        int x = 0;
        int y = r;
        int P = 1 - r;
        while (x <= y) {
            add_points(x, y);
            x += 1;
            if (P < 0) {
                P += 2 * x + 1;
            } else {
                y -= 1;
                P += 2 * (x - y) + 1;
            }
        }
    }

    void render(sf::RenderWindow& window) {
        for (auto& p : points) {
            sf::Vertex point{
                sf::Vector2f(static_cast<float>(p.first), static_cast<float>(p.second)),
                color
            };
            window.draw(&point, 1, sf::PrimitiveType::Points);
        }
    }
};

#endif