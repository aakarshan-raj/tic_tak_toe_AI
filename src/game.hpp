#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <random>

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

    sf::RenderWindow window_;
    sf::Font font;
    int positions_[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    std::vector<std::vector<int>> available_spots;
    int game_number{0};
    int last_move{2};
    int type_{1};
    std::map<int, int> winner;
    sf::Event event_;
    bool running{true};
    int width_ = 600;
    int height_ = 600;
    int full_width = 900;
    void init();
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

    std::random_device dev;
    std::mt19937 mt{dev()};

public:
    explicit Game(){};

    // Type  1: Human vs Human
    // Type  2: Human vs Machine
    // Type  3: Machine vs Machine
    // O - Machine
    // X - Human
    // O goes first for start = 2
    // X goes first for start = 1
    Game(int type, int start) : last_move(start), type_(type)
    {
    }
    void run();
};