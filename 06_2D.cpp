#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;
int main() {
  const float width = 500.0f;
  const float height = 500.0f;
  const float originX = width / 2.0f;
  const float originY = height / 2.0f;
  float x1 = -100.0f, y1 = -50.0f;
  float x2 = -50.0f, y2 = -50.0f;
  int ch;
  float nx1 = x1, ny1 = y1, nx2 = x2, ny2 = y2;
  cout << "Enter the desired transformation:\n";
  cout << "1. Translation\n";
  cout << "2. Rotation\n";
  cout << "3. Scaling\n";
  cout << "4. Shearing\n";
  cout << "5. Reflection\n";
  cin >> ch;
  switch (ch) {
    case 1: {
      float tx, ty;
      cout << "Enter the translation factors (tx, ty): ";
      cin >> tx >> ty;
      nx1 = x1 + tx;
      ny1 = y1 + ty;
      nx2 = x2 + tx;
      ny2 = y2 + ty;
      break;
    }
    case 2: {
      float angleDeg, xf, yf;
      cout << "Enter angle (in degrees): ";
      cin >> angleDeg;
      cout << "Enter the point of rotation (xf, yf): ";
      cin >> xf >> yf;
      float angleRad = angleDeg * 3.14159265358979323846f / 180.0f;
      float c = cos(angleRad);
      float s = sin(angleRad);
      float rx1 = x1 - xf, ry1 = y1 - yf;
      float rx2 = x2 - xf, ry2 = y2 - yf;
      nx1 = rx1 * c - ry1 * s + xf;
      ny1 = rx1 * s + ry1 * c + yf;
      nx2 = rx2 * c - ry2 * s + xf;
      ny2 = rx2 * s + ry2 * c + yf;
      break;
    }
    case 3: {
      float sx, sy, xf, yf;
      cout << "Enter the scaling factors (sx, sy): ";
      cin >> sx >> sy;
      cout << "Enter the fixed point (xf, yf): ";
      cin >> xf >> yf;
      nx1 = x1 * sx + xf * (1.0f - sx);
      ny1 = y1 * sy + yf * (1.0f - sy);
      nx2 = x2 * sx + xf * (1.0f - sx);
      ny2 = y2 * sy + yf * (1.0f - sy);
      break;
    }
    case 4: {
      float shx, shy;
      cout << "Enter shearing factors (shx, shy): ";
      cin >> shx >> shy;
      nx1 = x1 + shx * y1;
      ny1 = y1 + shy * x1;
      nx2 = x2 + shx * y2;
      ny2 = y2 + shy * x2;
      break;
    }
    case 5: {
      float m, c;
      cout << "Enter m and c for reflection line y = m*x + c: ";
      cin >> m >> c;
      float a = m;
      float b = -1.0f;
      float d = c;
      float denom = a * a + b * b;
      float factor1 = 2.0f * (a * x1 + b * y1 + d) / denom;
      nx1 = x1 - a * factor1;
      ny1 = y1 - b * factor1;
      float factor2 = 2.0f * (a * x2 + b * y2 + d) / denom;
      nx2 = x2 - a * factor2;
      ny2 = y2 - b * factor2;
      break;
    }
    default:
      cout << "Invalid choice! Showing original line only.\n";
      nx1 = x1;
      ny1 = y1;
      nx2 = x2;
      ny2 = y2;
  }
  cout << "Original line endpoints: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")\n";
  cout << "Transformed endpoints: (" << nx1 << ", " << ny1 << ") and (" << nx2 << ", " << ny2 << ")\n";
  auto toScreen = [&](float x, float y) {
    return sf::Vector2f(originX + x, originY - y);
  };
  auto makeThickLine = [&](float ax, float ay, float bx, float by, float thickness, sf::Color color) {
    sf::Vector2f p1 = toScreen(ax, ay);
    sf::Vector2f p2 = toScreen(bx, by);
    sf::Vector2f delta = p2 - p1;
    float length = sqrt(delta.x * delta.x + delta.y * delta.y);
    float angleDeg = atan2(delta.y, delta.x) * 180.0f / 3.14159265358979323846f;
    sf::RectangleShape line(sf::Vector2f(length, thickness));
    line.setFillColor(color);
    line.setOrigin(sf::Vector2f(0.0f, thickness / 2.0f));
    line.setPosition(p1);
    line.setRotation(sf::degrees(angleDeg));
    return line;
  };
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(static_cast<unsigned int>(width), static_cast<unsigned int>(height))), "081BCT049");
  sf::Vertex xAxis[] = {
    {sf::Vector2f(0.0f, originY), sf::Color(150, 150, 150)},
    {sf::Vector2f(width, originY), sf::Color(150, 150, 150)}
  };
  sf::Vertex yAxis[] = {
    {sf::Vector2f(originX, 0.0f), sf::Color(150, 150, 150)},
    {sf::Vector2f(originX, height), sf::Color(150, 150, 150)}
  };
  sf::RectangleShape originalLine = makeThickLine(x1, y1, x2, y2, 3.0f, sf::Color(0, 0, 140));
  sf::RectangleShape transformedLine = makeThickLine(nx1, ny1, nx2, ny2, 3.0f, sf::Color(180, 0, 0));
  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    window.draw(xAxis, 2, sf::PrimitiveType::Lines);
    window.draw(yAxis, 2, sf::PrimitiveType::Lines);
    window.draw(originalLine);
    window.draw(transformedLine);
    window.display();
  }
  return 0;
}
// g++ -std=c++17 06_2D.cpp -o 06_2D -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./06_2D