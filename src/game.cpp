#include "game.hpp"

void Game::init()
{
    window_.create(sf::VideoMode(width_, height_), "Tic Tac Toe");
    game_number = 1;
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
        if (event_.type == sf::Event::MouseButtonPressed)
        {
            if (event_.mouseButton.button == sf::Mouse::Left)
            {
                auto pos = click_box(event_.mouseButton.x, event_.mouseButton.y);
                positions_[pos.x][pos.y] = 2;
            }
            else if (event_.mouseButton.button == sf::Mouse::Right)
            {
                auto pos = click_box(event_.mouseButton.x, event_.mouseButton.y);
                positions_[pos.x][pos.y] = 1;
            }
            check_winner();
        }
    }
}

void Game::draw_horizontal_lines()
{
    sf::RectangleShape line1(sf::Vector2f(width_, 3));
    sf::RectangleShape line2(sf::Vector2f(width_, 3));
    line1.setFillColor(sf::Color::Black);
    line1.setPosition(sf::Vector2f(0, height_ / 3));

    line2.setFillColor(sf::Color::Black);
    line2.setPosition(sf::Vector2f(0, 2 * (height_ / 3)));
    window_.draw(line1);
    window_.draw(line2);
}

void Game::draw_vertical_lines()
{
    sf::RectangleShape line1(sf::Vector2f(height_, 3));
    sf::RectangleShape line2(sf::Vector2f(height_, 3));
    line1.setFillColor(sf::Color::Black);
    line1.setPosition(sf::Vector2f(width_ / 3, 0));
    line1.rotate(90);

    line2.setFillColor(sf::Color::Black);
    line2.setPosition(sf::Vector2f((width_ / 3) * 2, 0));
    line2.rotate(90);
    window_.draw(line1);
    window_.draw(line2);
}

sf::Vector2<int> Game::click_box(int x, int y)
{
    sf::Vector2<int> box;
    if (x > 400)
    {
        box.x = 2;
        if (y > 400)
        {
            box.y = 2;
        }
        else if (y > 200)
        {
            box.y = 1;
        }
        else
        {
            box.y = 0;
        }
    }
    else if (x > 200)
    {
        box.x = 1;
        if (y > 400)
        {
            box.y = 2;
        }
        else if (y > 200)
        {
            box.y = 1;
        }
        else
        {
            box.y = 0;
        }
    }
    else
    {
        box.x = 0;
        if (y > 400)
        {
            box.y = 2;
        }
        else if (y > 200)
        {
            box.y = 1;
        }
        else
        {
            box.y = 0;
        }
    }
    return box;
}

void Game::draw_o(int x, int y)
{
    sf::CircleShape shape(70);
    shape.setOrigin(sf::Vector2f(70, 70));
    shape.setPosition(100 + (x * 200), 100 + (y * 200));
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::Black);
    window_.draw(shape);
}

void Game::draw_x(int x, int y)
{
    sf::RectangleShape line1(sf::Vector2f(200, 5));
    line1.rotate(45);
    line1.setFillColor(sf::Color::Black);
    line1.setPosition(sf::Vector2f(30 + (200 * x), 30 + (200 * y)));

    sf::RectangleShape line2(sf::Vector2f(200, 5));
    line2.rotate(90 + 45);
    line2.setFillColor(sf::Color::Black);
    line2.setPosition(sf::Vector2f(170 + (200 * x), 30 + (200 * y)));

    window_.draw(line1);
    window_.draw(line2);
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
                draw_x(i, j);
            }
            else if (positions_[i][j] == 2)
            {
                draw_o(i, j);
            }
        }
    }
}

void Game::restart()
{
    game_number++;
    render();
    sleep(1);
    std::memset(positions_, 0, sizeof positions_);
}

bool Game::check_winner()
{
    // 8 checks

    for (int i = 0; i < 3; i++)
    {
        int z = positions_[i][0] & positions_[i][1] & positions_[i][2];
        if (z != 0)
        {
            winner.push_back(z);
            restart();
            return true;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        int z = positions_[0][i] & positions_[1][i] & positions_[2][i];
        if (z != 0)
        {
            winner.push_back(z);
            restart();
            return true;
        }
    }
    int z = positions_[0][0] & positions_[1][1] & positions_[2][2];
    if (z != 0)
    {
        winner.push_back(z);
        restart();
        return true;
    }
    int y = positions_[0][2] & positions_[1][1] & positions_[2][0];
    if (y != 0)
    {
        winner.push_back(y);
        restart();
        return true;
    }
}