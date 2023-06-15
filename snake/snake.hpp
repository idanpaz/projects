#include <SFML/Graphics.hpp>
#include <sys/types.h>
#include <random>
#include <vector>
#include <sqlite3.h>

enum Dir
{
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};

class BoardObjects
{
public:
    virtual ~BoardObjects() {}
    virtual void Draw(sf::RenderWindow &window) = 0;
};

class Snake : public BoardObjects
{
public:
    explicit Snake(u_int16_t initialSize, u_int16_t pointRadius);
    void Draw(sf::RenderWindow &window);

    void MoveSnake(Dir dir);
    std::vector<sf::CircleShape> &GetSnakeContainer();

private:
    void AddPoint(u_int16_t x, u_int16_t y);

    std::vector<sf::CircleShape> m_vector;
    u_int16_t m_pointRadius;
};

class Food : public BoardObjects
{
public:
    explicit Food(u_int16_t radius, u_int16_t m_boardWidth, u_int16_t boardHeight);
    void Draw(sf::RenderWindow &window);

    sf::CircleShape &GetFoodObj();
    u_int16_t GetRandomXPosition();
    u_int16_t GetRandomYPosition();

private:
    std::random_device m_rd;
    sf::CircleShape m_foodObj;
    u_int16_t m_radius;
    u_int16_t m_boardWidth;
    u_int16_t m_boardHeight;
};

class SnakeUI : public BoardObjects
{
public:
    explicit SnakeUI(u_int16_t boardWidth);
    void Draw(sf::RenderWindow &window);

    sf::Text &GetScoreText();
    sf::Text &GetLevelText();

private:
    sf::Text m_yourScoreText;
    sf::Text m_scoreText;
    sf::Text m_yourLevelText;
    sf::Text m_levelText;
    sf::RectangleShape m_topBorder;
    sf::Font m_font;
    u_int16_t m_boardWidth;
};

class Board
{
public:
    explicit Board(u_int16_t width, u_int16_t height, std::string title,
                   u_int16_t initialSnakeSize, u_int16_t pointRadius);
    ~Board();

    sf::RenderWindow &GetWindow();
    std::vector<BoardObjects *> &GetBoardObjects();

private:
    sf::RenderWindow m_window;
    std::vector<BoardObjects *> m_boardObjects;
};

class GameEngine
{
public:
    explicit GameEngine(u_int16_t width, u_int16_t height, std::string title,
                        u_int16_t initialSnakeSize, u_int16_t pointRadius,
                        std::string username);

    void Run();

private:
    void DisplayBoardObjects(sf::Clock &clock);
    void ChangeDir(sf::Event &event);
    void CheckFood();
    void CheckDeath();
    void WriteScoreToDB(std::string username, std::string score);

    Board m_board;
    Dir m_dir;
    bool m_shouldRun;
    u_int16_t m_score;
    u_int16_t m_level;
    u_int16_t m_frameTime;
    std::string m_username;
    sqlite3 *m_scoreDB;
};
