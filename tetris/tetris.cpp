#include <unordered_map>

#include "tetris.hpp"

#define SQSIZE 25

LShape::LShape() : m_currOrrientation(0)
{
    u_int16_t x = 175;
    u_int16_t y = 0;
    
    m_matrix[0][0].setFillColor(sf::Color::Blue);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Blue);
    m_matrix[1][1].setFillColor(sf::Color::Black);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Blue);
    m_matrix[2][1].setFillColor(sf::Color::Blue);
    m_matrix[2][2].setFillColor(sf::Color::Black);

    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += SQSIZE;
        }

        y += SQSIZE;
        x = 175;
    }
}

void LShape::Draw(sf::RenderWindow& window)
{
    u_int8_t i = 0, j = 0;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            if (m_matrix[i][j].getFillColor() != sf::Color::Black)
                window.draw(m_matrix[i][j]);
        }
    }
}

void LShape::RotateLeft() 
{
    if (m_currOrrientation == 0)
    {
        m_currOrrientation = 270;
    }

    else
    {
        m_currOrrientation -= 90;
    }

    if (m_currOrrientation == 0)
    {
        m_matrix[0][0].setFillColor(sf::Color::Blue);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Blue);
        m_matrix[1][1].setFillColor(sf::Color::Black);
        m_matrix[1][2].setFillColor(sf::Color::Black);
        m_matrix[2][0].setFillColor(sf::Color::Blue);
        m_matrix[2][1].setFillColor(sf::Color::Blue);
        m_matrix[2][2].setFillColor(sf::Color::Black);     
    }

    else if (m_currOrrientation == 90)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Blue);
        m_matrix[1][1].setFillColor(sf::Color::Blue);
        m_matrix[1][2].setFillColor(sf::Color::Blue);
        m_matrix[2][0].setFillColor(sf::Color::Blue);
        m_matrix[2][1].setFillColor(sf::Color::Black);
        m_matrix[2][2].setFillColor(sf::Color::Black);
    }

    else if (m_currOrrientation == 180)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Blue);
        m_matrix[0][2].setFillColor(sf::Color::Blue);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Black);
        m_matrix[1][2].setFillColor(sf::Color::Blue);
        m_matrix[2][0].setFillColor(sf::Color::Black);
        m_matrix[2][1].setFillColor(sf::Color::Black);
        m_matrix[2][2].setFillColor(sf::Color::Blue);
    }

    else if (m_currOrrientation == 270)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Black);
        m_matrix[1][2].setFillColor(sf::Color::Blue);
        m_matrix[2][0].setFillColor(sf::Color::Blue);
        m_matrix[2][1].setFillColor(sf::Color::Blue);
        m_matrix[2][2].setFillColor(sf::Color::Blue);
    }
}

void LShape::MoveLeft() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x - SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void LShape::MoveRight() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x + SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void LShape::MoveDown()
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x, 
                                       m_matrix[i][j].getPosition().y + SQSIZE);
        }
    }   
}

SquareShape::SquareShape() 
{
    u_int16_t x = 175;
    u_int16_t y = 0;
    
    m_matrix[0][0].setFillColor(sf::Color::Black);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Red);
    m_matrix[1][1].setFillColor(sf::Color::Red);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Red);
    m_matrix[2][1].setFillColor(sf::Color::Red);
    m_matrix[2][2].setFillColor(sf::Color::Black);

    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += SQSIZE;
        }

        y += SQSIZE;
        x = 175;
    }
}

void SquareShape::Draw(sf::RenderWindow& window)
{
    u_int8_t i = 0, j = 0;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            if (m_matrix[i][j].getFillColor() != sf::Color::Black)
                window.draw(m_matrix[i][j]);
        }
    }
}

void SquareShape::RotateLeft() {}

void SquareShape::MoveLeft() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x - SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void SquareShape::MoveRight() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x + SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void SquareShape::MoveDown()
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x, 
                                       m_matrix[i][j].getPosition().y + SQSIZE);
        }
    }   
}

PlusShape::PlusShape() : m_currOrrientation(0)
{
    u_int16_t x = 175;
    u_int16_t y = 0;
    
    m_matrix[0][0].setFillColor(sf::Color::Black);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Black);
    m_matrix[1][1].setFillColor(sf::Color::Yellow);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Yellow);
    m_matrix[2][1].setFillColor(sf::Color::Yellow);
    m_matrix[2][2].setFillColor(sf::Color::Yellow);

    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += SQSIZE;
        }

        y += SQSIZE;
        x = 175;
    }
}

void PlusShape::Draw(sf::RenderWindow& window)
{
    u_int8_t i = 0, j = 0;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            if (m_matrix[i][j].getFillColor() != sf::Color::Black)
                window.draw(m_matrix[i][j]);
        }
    }
}

void PlusShape::RotateLeft() 
{
    if (m_currOrrientation == 0)
    {
        m_currOrrientation = 270;
    }

    else
    {
        m_currOrrientation -= 90;
    }

    if (m_currOrrientation == 0)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Yellow);
        m_matrix[1][2].setFillColor(sf::Color::Black);
        m_matrix[2][0].setFillColor(sf::Color::Yellow);
        m_matrix[2][1].setFillColor(sf::Color::Yellow);
        m_matrix[2][2].setFillColor(sf::Color::Yellow);     
    }

    else if (m_currOrrientation == 90)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Yellow);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Yellow);
        m_matrix[1][2].setFillColor(sf::Color::Yellow);
        m_matrix[2][0].setFillColor(sf::Color::Black);
        m_matrix[2][1].setFillColor(sf::Color::Black);
        m_matrix[2][2].setFillColor(sf::Color::Yellow);
    }

    else if (m_currOrrientation == 180)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Yellow);
        m_matrix[1][1].setFillColor(sf::Color::Yellow);
        m_matrix[1][2].setFillColor(sf::Color::Yellow);
        m_matrix[2][0].setFillColor(sf::Color::Black);
        m_matrix[2][1].setFillColor(sf::Color::Yellow);
        m_matrix[2][2].setFillColor(sf::Color::Black);
    }

    else if (m_currOrrientation == 270)
    {
        m_matrix[0][0].setFillColor(sf::Color::Yellow);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Yellow);
        m_matrix[1][1].setFillColor(sf::Color::Yellow);
        m_matrix[1][2].setFillColor(sf::Color::Black);
        m_matrix[2][0].setFillColor(sf::Color::Yellow);
        m_matrix[2][1].setFillColor(sf::Color::Black);
        m_matrix[2][2].setFillColor(sf::Color::Black);
    }
}

void PlusShape::MoveLeft() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x - SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void PlusShape::MoveRight() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x + SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void PlusShape::MoveDown()
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x, 
                                       m_matrix[i][j].getPosition().y + SQSIZE);
        }
    }   
}

LineShape::LineShape() : m_currOrrientation(0)
{
    u_int16_t x = 175;
    u_int16_t y = 0;
    
    m_matrix[0][0].setFillColor(sf::Color::Black);
    m_matrix[0][1].setFillColor(sf::Color::Green);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Black);
    m_matrix[1][1].setFillColor(sf::Color::Green);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Black);
    m_matrix[2][1].setFillColor(sf::Color::Green);
    m_matrix[2][2].setFillColor(sf::Color::Black);   

    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += SQSIZE;
        }

        y += SQSIZE;
        x = 175;
    }
}

void LineShape::Draw(sf::RenderWindow& window)
{
    u_int8_t i = 0, j = 0;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            if (m_matrix[i][j].getFillColor() != sf::Color::Black)
                window.draw(m_matrix[i][j]);
        }
    }
}

void LineShape::RotateLeft() 
{
    if (m_currOrrientation == 0)
    {
        m_currOrrientation = 90;
    }

    else
    {
        m_currOrrientation -= 90;
    }

    if (m_currOrrientation == 0)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Green);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Green);
        m_matrix[1][2].setFillColor(sf::Color::Black);
        m_matrix[2][0].setFillColor(sf::Color::Black);
        m_matrix[2][1].setFillColor(sf::Color::Green);
        m_matrix[2][2].setFillColor(sf::Color::Black);     
    }

    else if (m_currOrrientation == 90)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Black);
        m_matrix[1][2].setFillColor(sf::Color::Black);
        m_matrix[2][0].setFillColor(sf::Color::Green);
        m_matrix[2][1].setFillColor(sf::Color::Green);
        m_matrix[2][2].setFillColor(sf::Color::Green);
    }
}

void LineShape::MoveLeft() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x - SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void LineShape::MoveRight() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x + SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void LineShape::MoveDown()
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x, 
                                       m_matrix[i][j].getPosition().y + SQSIZE);
        }
    }   
}

SShape::SShape() : m_currOrrientation(0)
{
    u_int16_t x = 175;
    u_int16_t y = 0;
    
    m_matrix[0][0].setFillColor(sf::Color::Magenta);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Magenta);
    m_matrix[1][1].setFillColor(sf::Color::Magenta);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Black);
    m_matrix[2][1].setFillColor(sf::Color::Magenta);
    m_matrix[2][2].setFillColor(sf::Color::Black);   

    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += SQSIZE;
        }

        y += SQSIZE;
        x = 175;
    }
}

void SShape::Draw(sf::RenderWindow& window)
{
    u_int8_t i = 0, j = 0;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            if (m_matrix[i][j].getFillColor() != sf::Color::Black)
                window.draw(m_matrix[i][j]);
        }
    }
}

void SShape::RotateLeft() 
{
    if (m_currOrrientation == 0)
    {
        m_currOrrientation = 270;
    }

    else
    {
        m_currOrrientation -= 90;
    }

    if (m_currOrrientation == 0)
    {
        m_matrix[0][0].setFillColor(sf::Color::Magenta);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Magenta);
        m_matrix[1][1].setFillColor(sf::Color::Magenta);
        m_matrix[1][2].setFillColor(sf::Color::Black);
        m_matrix[2][0].setFillColor(sf::Color::Black);
        m_matrix[2][1].setFillColor(sf::Color::Magenta);
        m_matrix[2][2].setFillColor(sf::Color::Black);     
    }

    else if (m_currOrrientation == 90)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Magenta);
        m_matrix[1][2].setFillColor(sf::Color::Magenta);
        m_matrix[2][0].setFillColor(sf::Color::Magenta);
        m_matrix[2][1].setFillColor(sf::Color::Magenta);
        m_matrix[2][2].setFillColor(sf::Color::Black);
    }

    else if (m_currOrrientation == 180)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Magenta);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Magenta);
        m_matrix[1][2].setFillColor(sf::Color::Magenta);
        m_matrix[2][0].setFillColor(sf::Color::Black);
        m_matrix[2][1].setFillColor(sf::Color::Black);
        m_matrix[2][2].setFillColor(sf::Color::Magenta);
    }

    else if (m_currOrrientation == 270)
    {
        m_matrix[0][0].setFillColor(sf::Color::Black);
        m_matrix[0][1].setFillColor(sf::Color::Black);
        m_matrix[0][2].setFillColor(sf::Color::Black);
        m_matrix[1][0].setFillColor(sf::Color::Black);
        m_matrix[1][1].setFillColor(sf::Color::Magenta);
        m_matrix[1][2].setFillColor(sf::Color::Magenta);
        m_matrix[2][0].setFillColor(sf::Color::Magenta);
        m_matrix[2][1].setFillColor(sf::Color::Magenta);
        m_matrix[2][2].setFillColor(sf::Color::Black);
    }
}

void SShape::MoveLeft() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x - SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void SShape::MoveRight() 
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x + SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void SShape::MoveDown()
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x, 
                                       m_matrix[i][j].getPosition().y + SQSIZE);
        }
    }   
}

Board::Board(u_int16_t width, u_int16_t height, std::string title) :
m_window(sf::VideoMode(width, height), title.c_str()), m_currPiece(nullptr) {}

Board::~Board()
{
    for (IShape *piece : m_staticPieces)
    {
        delete piece;
    }

    if (m_currPiece)
    {
        delete m_currPiece;
    }
}

sf::RenderWindow& Board::GetWindow() { return m_window; }
std::vector<IShape *>& Board::GetShapesContainer() { return m_staticPieces; }
IShape * Board::GetCurrPiece() { return m_currPiece; }
void Board::SetCurrPiece(IShape *shape) { m_currPiece = shape; }

GameEngine::GameEngine(u_int16_t width, u_int16_t height, std::string title) :
m_board(width, height, title.c_str()), m_boardWidth(width), m_boardHeight(height),
m_frameTime(300), m_shouldRun(true), m_shapeOptions({ []()->IShape * { return new LShape; },
[]()->IShape * { return new SquareShape; }, []()->IShape * { return new PlusShape; },
[]()->IShape * { return new LineShape; }, []()->IShape * { return new SShape; }}) {}

void GameEngine::Run()
{
    sf::Clock clock;

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
                HandleInputs(event);          
            }
        }

        if (m_shouldRun && clock.getElapsedTime().asMilliseconds() >= m_frameTime)
        {
            if (!m_board.GetCurrPiece())
            {
                GenerateNewPiece();
            }

            DisplayBoardPieces();
            ScanRows();
            CheckDeath();

            clock.restart();
        }
    }
}

void GameEngine::HandleInputs(sf::Event& event)
{
    if (m_board.GetCurrPiece() && !IsOnFloor() && !IsOnOtherPiece())
    {
        if (event.key.code == sf::Keyboard::Up &&
            !IsOnLeftEdge() && !IsOnRightEdge())
        {
            m_board.GetCurrPiece()->RotateLeft();
        }

        else if (event.key.code == sf::Keyboard::Left &&
                 !IsAsideOtherPiece() && !IsOnLeftEdge())
        {
            m_board.GetCurrPiece()->MoveLeft();
        }

        else if (event.key.code == sf::Keyboard::Right && 
                 !IsAsideOtherPiece() && !IsOnRightEdge())
        {
            m_board.GetCurrPiece()->MoveRight();
        }

        else if (event.key.code == sf::Keyboard::Down)
        {
            m_board.GetCurrPiece()->MoveDown();
        }

        DrawAllPieces();
    }
}

void GameEngine::GenerateNewPiece()
{
    IShape *shape = m_shapeOptions[GetRandomShape()]();
    m_board.SetCurrPiece(shape);
}

bool GameEngine::IsOnFloor()
{
    IShape *currPiece = m_board.GetCurrPiece();

    if (currPiece)
    {
        for (u_int8_t i = 0; i < 3; ++i)
        {
            if (currPiece->GetMatrix()[2][i].getFillColor() != sf::Color::Black && 
                currPiece->GetMatrix()[2][i].getPosition().y == m_boardHeight - SQSIZE)
            {
                return true;
            }
        }
    }

    return false;
}

bool GameEngine::IsOnOtherPiece()
{
    u_int16_t size = m_board.GetShapesContainer().size();
    IShape *currPiece = m_board.GetCurrPiece();
    std::vector<IShape *>& staticPieces = m_board.GetShapesContainer();

    for (u_int16_t s = 0; s < size; ++s) // runs on all staticPieces
    {
        for (u_int8_t i = 0; i < 3; ++i) // runs on currPiece rows
        {
            for (u_int8_t j = 0; j < 3; ++j) // runs on currPiece cols
            {
                for (u_int8_t k = 0; k < 3; ++k) // runs on currPiece from staticPieces rows
                {
                    for (u_int8_t p = 0; p < 3; ++p) // runs on currPiece from staticPieces cols
                    {
                        if (currPiece->GetMatrix()[i][j].getFillColor() != sf::Color::Black &&
                            staticPieces[s]->GetMatrix()[k][p].getFillColor() != sf::Color::Black &&
                            currPiece->GetMatrix()[i][j].getPosition().x ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().x && 
                            currPiece->GetMatrix()[i][j].getPosition().y + SQSIZE ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().y)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool GameEngine::IsAsideOtherPiece()
{
    u_int16_t size = m_board.GetShapesContainer().size();
    IShape *currPiece = m_board.GetCurrPiece();
    std::vector<IShape *>& staticPieces = m_board.GetShapesContainer();

    for (u_int16_t s = 0; s < size; ++s) 
    {
        for (u_int8_t i = 0; i < 3; ++i) 
        {
            for (u_int8_t j = 0; j < 3; ++j) 
            {
                for (u_int8_t k = 0; k < 3; ++k) 
                {
                    for (u_int8_t p = 0; p < 3; ++p) 
                    {
                        if (currPiece->GetMatrix()[i][j].getFillColor() != sf::Color::Black &&
                            staticPieces[s]->GetMatrix()[k][p].getFillColor() != sf::Color::Black &&
                            currPiece->GetMatrix()[i][j].getPosition().y ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().y && 
                            (currPiece->GetMatrix()[i][j].getPosition().x + SQSIZE ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().x || 
                            currPiece->GetMatrix()[i][j].getPosition().x - SQSIZE ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().x))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;   
}

bool GameEngine::IsOnLeftEdge()
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            if (m_board.GetCurrPiece()->GetMatrix()[i][j].getFillColor() != sf::Color::Black && 
                m_board.GetCurrPiece()->GetMatrix()[i][j].getPosition().x == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool GameEngine::IsOnRightEdge()
{
    for (u_int8_t i = 0; i < 3; ++i)
    {
        for (u_int8_t j = 0; j < 3; ++j)
        {
            if (m_board.GetCurrPiece()->GetMatrix()[i][j].getFillColor() != sf::Color::Black && 
                m_board.GetCurrPiece()->GetMatrix()[i][j].getPosition().x == m_boardWidth - SQSIZE)
            {
                return true;
            }
        }
    }

    return false;   
}

void GameEngine::DrawAllPieces()
{
    m_board.GetWindow().clear();

    if (m_board.GetCurrPiece())
    {
        m_board.GetCurrPiece()->Draw(m_board.GetWindow());
    }

    for (IShape *piece : m_board.GetShapesContainer())
    {
        piece->Draw(m_board.GetWindow());
    }

    m_board.GetWindow().display();
}

void GameEngine::DisplayBoardPieces()
{
    if (!IsOnFloor() && !IsOnOtherPiece())
    {
        m_board.GetCurrPiece()->MoveDown();
    }

    else
    {
        m_board.GetShapesContainer().push_back(m_board.GetCurrPiece());
        m_board.GetCurrPiece()->Draw(m_board.GetWindow());
        m_board.SetCurrPiece(nullptr);
    }

    DrawAllPieces();
}

void GameEngine::ScanRows()
{
    u_int16_t size = m_board.GetShapesContainer().size();
    std::unordered_map<u_int16_t, u_int16_t> map;
    u_int16_t fullRowHeight = 0;
    u_int8_t numRowsToErase = 0;

    for (u_int16_t s = 0; s < size; ++s)
    {
        for (u_int8_t i = 0; i < 3; ++i)
        {
            for (u_int8_t j = 0; j < 3; ++j)
            {
                if (m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getFillColor() != sf::Color::Black)
                {
                    map[m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y] +=
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().x;
                }
            }
        }
    }

    for (auto i : map)
    {
        if (i.second == 3000)
        {
            fullRowHeight = i.first;
            ++numRowsToErase;

            for (u_int16_t s = 0; s < size; ++s)
            {
                for (u_int8_t j = 0; j < 3; ++j)
                {
                    for (u_int8_t k = 0; k < 3; ++k)
                    {
                        if (m_board.GetShapesContainer()[s]->GetMatrix()[j][k].getPosition().y == i.first)
                        {
                            m_board.GetShapesContainer()[s]->GetMatrix()[j][k].setFillColor(sf::Color::Black);
                        }
                    }
                }
            }
        }
    }

    for (u_int16_t s = 0; s < size; ++s)
    {
        for (u_int8_t i = 0; i < 3; ++i)
        {
            for (u_int8_t j = 0; j < 3; ++j)
            {
                if (m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y < fullRowHeight)
                {
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].setPosition(
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().x,
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y + numRowsToErase*SQSIZE);
                }
            }
        }
    }
}

u_int16_t GameEngine::GetRandomShape()
{
    std::mt19937 gen(m_rd());
    std::uniform_int_distribution<u_int16_t> distrib(0, m_shapeOptions.size() - 1);

    return distrib(gen);
}

void GameEngine::CheckDeath()
{
    u_int16_t size = m_board.GetShapesContainer().size();

    for (u_int16_t s = 0; s < size; ++s)
    {
        for (u_int8_t i = 0; i < 3; ++i)
        {
            for (u_int8_t j = 0; j < 3; ++j)
            {
                if (m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y == 0 &&
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getFillColor() != sf::Color::Black)
                {
                    m_shouldRun = false;
                }
            }
        }
    }
}