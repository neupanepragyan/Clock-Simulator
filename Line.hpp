#pragma once

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
    sf::Color color;
public:
    vector<pair<int, int>> points;
    Line(int _x1, int _y1, int _x2, int _y2, sf::Color color_){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        dx = x2-x1;
        dy = y2-y1;
        color = color_;
    }
    void draw_algorithm(){
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
