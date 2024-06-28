#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Game
{

public:
    sf::RenderWindow window_;
    int positions_[3][3] = {{2, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int game_number{0};
    std::vector<int> winner;
    sf::Event event_;
    bool running{true};
    int width_ = 600;
    int height_ = 600;
    void init();
    void run();
    void render();
    void input();
    void draw_vertical_lines();
    void draw_horizontal_lines();
    void draw_x(int, int);
    void draw_o(int, int);
    void draw_symbols();
    sf::Vector2<int> click_box(int, int);
    void restart();
    void check_winner();
};