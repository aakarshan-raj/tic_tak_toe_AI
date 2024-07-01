#include "game.hpp"

void Game::init()
{
    window_.create(sf::VideoMode(full_width, height_), "Tic Tac Toe");
    if (!font.loadFromFile("font/Poppins-Regular.ttf"))
    {
        running = false;
        exit(-1);
    }
    available_spots = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
    stats_rect.setSize(sf::Vector2f(height_, full_width - width_));
    stats_rect.setFillColor(sf::Color::Black);
    stats_rect.setPosition(sf::Vector2f(full_width, 0));
    stats_rect.rotate(90);

    stat_text.setFont(font);
    stat_text.setPosition(sf::Vector2f(600, 0));
    stat_text.setString("Stats");
    stat_text.setCharacterSize(20);
    stat_text.setFillColor(sf::Color::Red);

    total_text.setFont(font);
    total_text.setPosition(sf::Vector2f(600, 40));
    total_text.setString("Total Matches:");
    total_text.setCharacterSize(20);
    total_text.setFillColor(sf::Color::Red);

    total_text_value.setFont(font);
    total_text_value.setPosition(sf::Vector2f(750, 40));
    total_text_value.setString("0");
    total_text_value.setCharacterSize(20);
    total_text_value.setFillColor(sf::Color::Red);

    x_text.setFont(font);
    x_text.setPosition(sf::Vector2f(600, 80));
    x_text.setString("X wins:");
    x_text.setCharacterSize(20);
    x_text.setFillColor(sf::Color::Red);

    o_text.setFont(font);
    o_text.setPosition(sf::Vector2f(600, 120));
    o_text.setString("O wins:");
    o_text.setCharacterSize(20);
    o_text.setFillColor(sf::Color::Red);

    x_text_value.setFont(font);
    x_text_value.setPosition(sf::Vector2f(670, 80));
    x_text_value.setString("0");
    x_text_value.setCharacterSize(20);
    x_text_value.setFillColor(sf::Color::Red);

    o_text_value.setFont(font);
    o_text_value.setPosition(sf::Vector2f(670, 120));
    o_text_value.setString("0");
    o_text_value.setCharacterSize(20);
    o_text_value.setFillColor(sf::Color::Red);

    draw_text.setFont(font);
    draw_text.setPosition(sf::Vector2f(600, 160));
    draw_text.setString("Draws:");
    draw_text.setCharacterSize(20);
    draw_text.setFillColor(sf::Color::Red);

    draw_text_value.setFont(font);
    draw_text_value.setPosition(sf::Vector2f(670, 160));
    draw_text_value.setString("0");
    draw_text_value.setCharacterSize(20);
    draw_text_value.setFillColor(sf::Color::Red);

    line1_h.setSize(sf::Vector2f(width_, 3));
    line2_h.setSize(sf::Vector2f(width_, 3));

    line1_h.setFillColor(sf::Color::Black);
    line1_h.setPosition(sf::Vector2f(0, height_ / 3));

    line2_h.setFillColor(sf::Color::Black);
    line2_h.setPosition(sf::Vector2f(0, 2 * (height_ / 3)));

    line1_v.setSize(sf::Vector2f(height_, 3));
    line2_v.setSize(sf::Vector2f(height_, 3));

    line1_v.setFillColor(sf::Color::Black);
    line1_v.setPosition(sf::Vector2f(width_ / 3, 0));
    line1_v.rotate(90);

    line2_v.setFillColor(sf::Color::Black);
    line2_v.setPosition(sf::Vector2f((width_ / 3) * 2, 0));
    line2_v.rotate(90);

    shape_o.setRadius(70);
    shape_o.setOrigin(sf::Vector2f(70, 70));
    shape_o.setOutlineThickness(3);
    shape_o.setOutlineColor(sf::Color::Black);

    cross_line1.setSize(sf::Vector2f(200, 5));
    cross_line1.rotate(45);
    cross_line1.setFillColor(sf::Color::Black);

    cross_line2.setSize(sf::Vector2f(200, 5));
    cross_line2.rotate(90 + 45);
    cross_line2.setFillColor(sf::Color::Black);
}

void Game::run()
{
    init();
    while (running)
    {
        render();
        input();
    }
    window_.close();
}

void Game::render()
{
    window_.clear(sf::Color::White);
    draw_symbols();
    draw_horizontal_lines();
    draw_vertical_lines();
    stats();
    window_.display();
}

void Game::input()
{
    while (window_.pollEvent(event_))
    {
        if (event_.type == sf::Event::Closed)
        {
            running = false;
        }
        if (event_.type == sf::Event::KeyPressed)
        {
            if (event_.key.code == sf::Keyboard::Escape)
            {
                running = false;
            }
        }
        if (type_ == 1)
        {
            if (event_.type == sf::Event::MouseButtonPressed)
            {
                human_move(event_.mouseButton.x, event_.mouseButton.y);
                check_winner();
            }
        }
        else if (type_ == 2)
        {
            if (last_move == 1)
            {
                if (event_.type == sf::Event::MouseButtonPressed)
                {
                    human_move(event_.mouseButton.x, event_.mouseButton.y);
                    check_winner();
                }
            }
        }
    }
    if (type_ == 3)
    {
        machine_move();
        check_winner();
    }
    if (type_ == 2)
    {
        if (last_move == 2)
        {
            machine_move();
            check_winner();
        }
    }
}

void Game::human_move(int x, int y)
{
    auto pos = click_box(x, y);
    if (positions_[pos.x][pos.y] == 0)
    {
        positions_[pos.x][pos.y] = last_move;
        available_spots.erase(std::remove(available_spots.begin(), available_spots.end(), std::vector<int>{pos.x, pos.y}), available_spots.end());
        last_move = (last_move == 2) ? 1 : (last_move == 1) ? 2
                                                            : last_move;
    }
}

void Game::machine_move()
{
    std::uniform_int_distribution<int> dist(0, available_spots.size() - 1);
    int random = dist(mt);
    int x = available_spots[random][0];
    int y = available_spots[random][1];

    positions_[x][y] = last_move;
    available_spots.erase(std::remove(available_spots.begin(), available_spots.end(), std::vector<int>{x, y}), available_spots.end());
    last_move = (last_move == 2) ? 1 : (last_move == 1) ? 2
                                                        : last_move;
}

void Game::draw_horizontal_lines()
{

    window_.draw(line1_h);
    window_.draw(line2_h);
}

void Game::draw_vertical_lines()
{

    window_.draw(line1_v);
    window_.draw(line2_v);
}

sf::Vector2<int> Game::click_box(int x, int y)
{
    sf::Vector2<int> box;
    if (x > 400)
    {
        box.y = 2;
        if (y > 400)
        {
            box.x = 2;
        }
        else if (y > 200)
        {
            box.x = 1;
        }
        else
        {
            box.x = 0;
        }
    }
    else if (x > 200)
    {
        box.y = 1;
        if (y > 400)
        {
            box.x = 2;
        }
        else if (y > 200)
        {
            box.x = 1;
        }
        else
        {
            box.x = 0;
        }
    }
    else
    {
        box.y = 0;
        if (y > 400)
        {
            box.x = 2;
        }
        else if (y > 200)
        {
            box.x = 1;
        }
        else
        {
            box.x = 0;
        }
    }
    return box;
}

void Game::draw_o(int x, int y)
{
    shape_o.setPosition(100 + (x * 200), 100 + (y * 200));
    window_.draw(shape_o);
}

void Game::draw_x(int x, int y)
{

    cross_line1.setPosition(sf::Vector2f(30 + (200 * x), 30 + (200 * y)));
    cross_line2.setPosition(sf::Vector2f(170 + (200 * x), 30 + (200 * y)));

    window_.draw(cross_line1);
    window_.draw(cross_line2);
}

void Game::draw_symbols()
{
    // 0: empty
    // 1: X
    // 2: O
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (positions_[i][j] == 1)
            {
                draw_x(j, i);
            }
            else if (positions_[i][j] == 2)
            {
                draw_o(j, i);
            }
        }
    }
}

void Game::restart()
{
    game_number++;
    render();
    if (wait_between_game_ != 0)
    {
        sleep(wait_between_game_);
    }
    std::memset(positions_, 0, sizeof positions_);
    available_spots = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
}

bool Game::check_winner()
{
    // 8 checks

    for (int i = 0; i < 3; i++)
    {
        int z = positions_[i][0] & positions_[i][1] & positions_[i][2];
        if (z != 0)
        {
            winner[z]++;
            restart();
            return true;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        int z = positions_[0][i] & positions_[1][i] & positions_[2][i];
        if (z != 0)
        {
            winner[z]++;
            restart();
            return true;
        }
    }
    int z = positions_[0][0] & positions_[1][1] & positions_[2][2];
    if (z != 0)
    {
        winner[z]++;
        restart();
        return true;
    }
    int y = positions_[0][2] & positions_[1][1] & positions_[2][0];
    if (y != 0)
    {
        winner[y]++;
        restart();
        return true;
    }
    bool draw = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (positions_[i][j] == 0)
            {
                draw = false;
                goto end;
            }
        }
    }
end:
    if (draw)
    {
        winner[0]++;
        restart();
        return true;
    }
    if (wait_between_move_ != 0)
    {
        sleep(wait_between_move_);
    }
    return true;
}

void Game::stats()
{

    total_text_value.setString(std::to_string(game_number));
    x_text_value.setString(std::to_string(winner[1]));
    o_text_value.setString(std::to_string(winner[2]));
    draw_text_value.setString(std::to_string(winner[0]));

    window_.draw(stats_rect);
    window_.draw(stat_text);
    window_.draw(x_text);
    window_.draw(o_text);
    window_.draw(x_text_value);
    window_.draw(o_text_value);
    window_.draw(total_text);
    window_.draw(total_text_value);
    window_.draw(draw_text);
    window_.draw(draw_text_value);
}

void Game::minimax(int position[3][3], int depth, bool turn)
{
}