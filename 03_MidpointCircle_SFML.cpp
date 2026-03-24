#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
using namespace std;
class Circle {
private:
    int x_c ;
    int y_c ;
    int r ;
public:
    vector<pair<int, int>> points;
    Circle(int x_= 0, int y_= 0, int r_= 2){
        x_c = x_;
        y_c = y_;
        r = r_;
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
    void draw(){
        int x = 0;
        int y = r;
        int P = 1 - r;
        while (x <= y){
            add_points(x, y);
            x += 1;
            if (P < 0){
                P += 2 * x + 1;
            }
            else{
                y -= 1;
                P += 2 * (x - y) + 1;
            }
        }
    }
};  

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(400, 400)), "Midpoint Circle");
    Circle C(200, 200, 80);
    C.draw();
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        for (auto& p : C.points) {
            sf::Vertex point{
                sf::Vector2f(static_cast<float>(p.first), static_cast<float>(p.second)),
                sf::Color::White
            };
            window.draw(&point, 1, sf::PrimitiveType::Points);
        }
        window.display();
    }
    return 0;
}

//g++ -std=c++17 03_MidpointCircle_SFML.cpp -o 03_MidpointCircle_SFML -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./03_MidpointCircle_SFML