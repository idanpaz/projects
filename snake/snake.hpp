#include <SFML/Graphics.hpp>
#include <sys/types.h>
#include <random>
#include <vector>

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

    std::vector<sf::CircleShape> &GetSnakeContainer();
    u_int16_t GetRadius();

private:
    std::vector<sf::CircleShape> m_vector;
    u_int16_t m_pointRadius;
};

class Board
{
public:
    explicit Board(u_int16_t width, u_int16_t height, std::string title,
                   u_int16_t initialSnakeSize, u_int16_t pointRadius);

    sf::RenderWindow &GetWindow();
    sf::CircleShape &GetFood();
    Snake &GetSnake();

    u_int16_t GetRandomXPosition();
    u_int16_t GetRandomYPosition();

private:
    sf::RenderWindow m_window;
    sf::CircleShape m_food;
    Snake m_snake;
    std::random_device m_rd;
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