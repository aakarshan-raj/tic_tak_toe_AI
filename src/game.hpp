#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>

class Game
{

private:
    sf::RectangleShape stats_rect;
    sf::Text stat_text;
    sf::Text x_text;
    sf::Text o_text;
    sf::Text total_text;
    sf::Text total_text_value;
    sf::Text x_text_value;
    sf::Text o_text_value;

    sf::Text draw_text;
    sf::Text draw_text_value;


    sf::RectangleShape line1_h;
    sf::RectangleShape line2_h;

    sf::RectangleShape line1_v;
    sf::RectangleShape line2_v;

    sf::CircleShape shape_o;

    sf::RectangleShape cross_line1;
    sf::RectangleShape cross_line2;



public:
    sf::RenderWindow window_;
    sf::Font font;
    int positions_[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int game_number{0};
    int last_move{2};
    std::map<int, int> winner;
    sf::Event event_;
    bool running{true};
    int width_ = 600;
    int height_ = 600;
    int full_width = 800;
    void init();
    void run();
    void render();
    void input();
    void stats();
    void draw_vertical_lines();
    void draw_horizontal_lines();
    void draw_x(int, int);
    void draw_o(int, int);
    void draw_symbols();
    sf::Vector2<int> click_box(int, int);
    void restart();
    bool check_winner();
};