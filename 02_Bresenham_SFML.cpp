#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
using namespace std;
int abs(int n){
    if (n < 0){
        return -n;
    }
    else
        return n;
}
class Line {
private:
    int x1;
    int x2;
    int y1;
    int y2;
    int dx;
    int dy;
public:
    vector<pair<int, int>> points;
    Line(int _x1, int _y1, int _x2, int _y2){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        dx = x2-x1;
        dy = y2-y1;
    }
    void BresenhamLine(){
        int Ix, Iy;
        Ix = (dx < 0) ? -1 : 1; //right->left or left->right
        Iy = (dy < 0) ? -1 : 1; //up->down or down->up
        dx = abs(dx);
        dy = abs(dy);
        if (dx>dy){ //m < 1
            int P = 2 * dy - dx;
            int Pnext;
            do{
                points.push_back({x1, y1});
                x1 += Ix;
                if (P<0){
                    Pnext = P + 2 * dy;
                }
                else{
                    Pnext = P + 2 * dy - 2 * dx;
                    y1 += Iy;
                }
                P = Pnext;
            }while (x1!=x2);
        }
        else{
            int P = 2 * dx - dy;
            int Pnext;
            do{
                points.push_back({x1, y1});
                y1 += Iy;
                if (P<0){
                    Pnext = P + 2 * dx;
                }
                else{
                    Pnext = P + 2 * dx - 2 * dy;
                    x1 += Ix;
                }
                P = Pnext;
            }while (y1!=y2);
        }
        points.push_back({x1, y1});
    }
};
int main() {   
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(400, 400)), "Bresenham Line");
    Line l1(50, 50, 350, 200);
    Line l2(350, 200, 50, 50);
    Line l3(50, 50, 200, 350);
    Line l4(50, 350, 200, 50);
    l1.BresenhamLine();
    l2.BresenhamLine();
    l3.BresenhamLine();
    l4.BresenhamLine();
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        auto drawPoints = [&](const vector<pair<int, int>>& pts, sf::Color color) {
            for (auto& p : pts) {
                sf::Vertex point{
                    sf::Vector2f(static_cast<float>(p.first), static_cast<float>(p.second)),
                    color
                };
                window.draw(&point, 1, sf::PrimitiveType::Points);
            }
        };
        drawPoints(l1.points, sf::Color::White);
        drawPoints(l2.points, sf::Color::Green);
        drawPoints(l3.points, sf::Color::Cyan);
        drawPoints(l4.points, sf::Color::Red);
        window.display();
    }
    return 0;
}

//g++ -std=c++17 02_Bresenham_SFML.cpp -o 02_Bresenham_SFML -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./02_Bresenham_SFML