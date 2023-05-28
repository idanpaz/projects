#include <SFML/Graphics.hpp>
#include <sys/types.h>
#include <deque>

enum dir
{
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};

class Snake
{
public:
    explicit Snake(u_int16_t initialSize, u_int16_t pointRadius);

    void AddPoint(u_int16_t x, u_int16_t y);
    void DrawSnake(sf::RenderWindow &window);

    std::deque<sf::CircleShape> &GetSnakeContainer();
    u_int16_t GetRadius();

private:
    std::deque<sf::CircleShape> m_deque;
    u_int16_t m_pointRadius;
};

class Food
{
public:
    explicit Food(u_int16_t initialXPos, u_int16_t initialYPos);

    void DrawFood(sf::RenderWindow &window, Snake &snake);

    u_int16_t GetXPosition();
    u_int16_t GetYPosition();

    void SetXPosition(u_int16_t xPos);
    void SetYPosition(u_int16_t yPos);

private:
    u_int16_t m_xPos;
    u_int16_t m_yPos;
};

class Board
{
public:
    explicit Board(u_int16_t width, u_int16_t height, std::string title,
                   u_int16_t initialSnakeSize, u_int16_t pointRadius);

    sf::RenderWindow &GetWindow();
    Snake &GetSnake();
    Food &GetFood();

    u_int16_t GetRandomXPosition();
    u_int16_t GetRandomYPosition();

private:
    sf::RenderWindow m_window;
    Snake m_snake;
    Food m_food;
};

class GameEngine
{
public:
    explicit GameEngine(u_int16_t width, u_int16_t height, std::string title,
                        u_int16_t initialSnakeSize, u_int16_t pointRadius);

    void Run();

private:
    void MoveSnake(sf::Clock &clockMove);
    void GenerateFood();
    void ExpandSnake();

    Board m_board;
    dir m_dir;
    bool m_shouldRun;
    size_t m_score;
};