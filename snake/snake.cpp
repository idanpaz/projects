#include "snake.hpp"

Snake::Snake(u_int16_t initialSnakeSize, u_int16_t pointRadius) : 
             m_pointRadius(pointRadius)
{
    u_int16_t x = 0;

    while (initialSnakeSize)
    {
        AddPoint(360 + x, 300);
        --initialSnakeSize;
        x += pointRadius * 2;
    }
}

void Snake::AddPoint(u_int16_t x, u_int16_t y)
{
    sf::CircleShape point(m_pointRadius);
    point.setFillColor(sf::Color::Green);
    point.setPosition(x, y);
    m_vector.insert(m_vector.begin(), point);
}

void Snake::DrawSnake(sf::RenderWindow& window)
{
    for (const auto& point : m_vector)
    {
        window.draw(point);
    }
}

std::vector<sf::CircleShape>& Snake::GetSnakeContainer() { return m_vector; }

u_int16_t Snake::GetRadius()
{
    return m_pointRadius;
}

Board::Board(u_int16_t width, u_int16_t height, std::string title, 
             u_int16_t initialSnakeSize, u_int16_t pointRadius) : 
             m_window(sf::VideoMode(width, height), title.c_str()), 
             m_snake(initialSnakeSize, pointRadius)
{
    m_food.setRadius(m_snake.GetRadius());
    m_food.setFillColor(sf::Color::Blue);
    m_food.setPosition(GetRandomXPosition(), GetRandomYPosition());
}

sf::RenderWindow& Board::GetWindow() { return m_window; }

sf::CircleShape& Board::GetFood() { return m_food; }

Snake& Board::GetSnake() { return m_snake; }

u_int16_t Board::GetRandomXPosition()
{
    std::mt19937 gen(m_rd());
    u_int16_t diameter = m_snake.GetRadius() * 2;
    std::uniform_int_distribution<u_int16_t> disX(0, 
    (m_window.getSize().x - diameter) / diameter);

    return disX(gen) * diameter;
}

u_int16_t Board::GetRandomYPosition()
{
    std::mt19937 gen(m_rd());
    u_int16_t diameter = m_snake.GetRadius() * 2;
    std::uniform_int_distribution<u_int16_t> disY(0, 
    (m_window.getSize().y - diameter) / diameter);

    return disY(gen) * diameter;
}

GameEngine::GameEngine(u_int16_t width, u_int16_t height, std::string title, 
                       u_int16_t initialSnakeSize, u_int16_t pointRadius) : 
                       m_board(width, height, title, initialSnakeSize, pointRadius),
                       m_dir(RIGHT), m_shouldRun(true) {}

void GameEngine::MoveSnake(sf::Clock& clockMove)
{
    if (clockMove.getElapsedTime().asMilliseconds() >= 100)
    {
        m_board.GetWindow().clear();
        m_board.GetSnake().DrawSnake(m_board.GetWindow());
        m_board.GetWindow().draw(m_board.GetFood());
        m_board.GetWindow().display();

        ExpandSnake();

        m_board.GetSnake().GetSnakeContainer().pop_back();
        clockMove.restart();
    }
}

void GameEngine::GenerateFood()
{
    if (m_board.GetSnake().GetSnakeContainer().front().getPosition() == 
        m_board.GetFood().getPosition())
    {
        m_board.GetFood().setPosition(m_board.GetRandomXPosition(), 
                                      m_board.GetRandomYPosition());

        ExpandSnake();
        ++m_score;
    }
}

void GameEngine::ExpandSnake()
{
    u_int16_t xPos = m_board.GetSnake().GetSnakeContainer().front().getPosition().x;
    u_int16_t yPos = m_board.GetSnake().GetSnakeContainer().front().getPosition().y;
    u_int16_t diameter = m_board.GetSnake().GetRadius() * 2;

    switch (m_dir)
    {
        case (LEFT):
        {
            m_board.GetSnake().AddPoint(xPos - diameter, yPos);

            break;
        }

        case (RIGHT):
        {
            m_board.GetSnake().AddPoint(xPos + diameter, yPos);

            break;
        }

        case UP:
        {
            m_board.GetSnake().AddPoint(xPos, yPos - diameter);

            break;
        }

        case DOWN:
        {
            m_board.GetSnake().AddPoint(xPos, yPos + diameter);

            break;
        }
    }
}

void GameEngine::Run()
{
    sf::Clock clockMove;

    while (m_board.GetWindow().isOpen())
    {
        sf::Event event;

        if (m_board.GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_board.GetWindow().close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up && m_dir != DOWN)
                {
                    m_dir = UP;
                }

                else if (event.key.code == sf::Keyboard::Down && m_dir != UP)
                {
                    m_dir = DOWN;
                }

                else if (event.key.code == sf::Keyboard::Left && m_dir != RIGHT)
                {
                    m_dir = LEFT;
                }

                else if (event.key.code == sf::Keyboard::Right && m_dir != LEFT)
                {
                    m_dir = RIGHT;
                }           
            }
        }

        if (m_shouldRun)
        {
            MoveSnake(clockMove);
            GenerateFood();
        }

        size_t size = m_board.GetSnake().GetSnakeContainer().size();
        auto frontPos = m_board.GetSnake().GetSnakeContainer().front().getPosition();
        auto xPos = m_board.GetSnake().GetSnakeContainer().front().getPosition().x;
        auto yPos = m_board.GetSnake().GetSnakeContainer().front().getPosition().y;

        if (xPos == m_board.GetWindow().getSize().x || xPos >= 65500 ||
            yPos == m_board.GetWindow().getSize().y || yPos >= 65500)
        {
            m_shouldRun = false;
        }

        for (size_t i = 1; i < size; ++i)
        {
            if (m_board.GetSnake().GetSnakeContainer()[i].getPosition() == frontPos)
            {
                m_shouldRun = false;
            }
        }
    }
}
