#include <unordered_map>

#include "tetris.hpp"

Shape::Shape() : m_currOrrientation(0) {}
Shape::~Shape() {}

void Shape::MoveLeft() 
{
    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x - Shape::SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void Shape::MoveRight() 
{
    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x + Shape::SQSIZE, 
                                       m_matrix[i][j].getPosition().y);
        }
    }
}

void Shape::MoveDown()
{
    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setPosition(m_matrix[i][j].getPosition().x, 
                                       m_matrix[i][j].getPosition().y + Shape::SQSIZE);
        }
    }   
}

void Shape::Draw(sf::RenderWindow& window)
{
    u_int8_t i = 0, j = 0;

    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLS; ++j)
        {
            if (m_matrix[i][j].getFillColor() != sf::Color::Black)
                window.draw(m_matrix[i][j]);
        }
    }    
}

sf::RectangleShape (&Shape::GetMatrix())[ROWS][COLS] { return m_matrix; }

LShape::LShape()
{
    u_int16_t x = INITIAL_XPOS;
    u_int16_t y = INITIAL_YPOS;
    
    m_matrix[0][0].setFillColor(sf::Color::Blue);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Blue);
    m_matrix[1][1].setFillColor(sf::Color::Black);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Blue);
    m_matrix[2][1].setFillColor(sf::Color::Blue);
    m_matrix[2][2].setFillColor(sf::Color::Black);

    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += Shape::SQSIZE;
        }

        y += Shape::SQSIZE;
        x = INITIAL_XPOS;
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

SquareShape::SquareShape() 
{
    u_int16_t x = INITIAL_XPOS;
    u_int16_t y = INITIAL_YPOS;
    
    m_matrix[0][0].setFillColor(sf::Color::Black);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Red);
    m_matrix[1][1].setFillColor(sf::Color::Red);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Red);
    m_matrix[2][1].setFillColor(sf::Color::Red);
    m_matrix[2][2].setFillColor(sf::Color::Black);

    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += Shape::SQSIZE;
        }

        y += Shape::SQSIZE;
        x = INITIAL_XPOS;
    }
}

void SquareShape::RotateLeft() {}

PlusShape::PlusShape()
{
    u_int16_t x = INITIAL_XPOS;
    u_int16_t y = INITIAL_YPOS;
    
    m_matrix[0][0].setFillColor(sf::Color::Black);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Black);
    m_matrix[1][1].setFillColor(sf::Color::Yellow);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Yellow);
    m_matrix[2][1].setFillColor(sf::Color::Yellow);
    m_matrix[2][2].setFillColor(sf::Color::Yellow);

    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += Shape::SQSIZE;
        }

        y += Shape::SQSIZE;
        x = INITIAL_XPOS;
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

LineShape::LineShape()
{
    u_int16_t x = INITIAL_XPOS;
    u_int16_t y = INITIAL_YPOS;
    
    m_matrix[0][0].setFillColor(sf::Color::Black);
    m_matrix[0][1].setFillColor(sf::Color::Green);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Black);
    m_matrix[1][1].setFillColor(sf::Color::Green);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Black);
    m_matrix[2][1].setFillColor(sf::Color::Green);
    m_matrix[2][2].setFillColor(sf::Color::Black);   

    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += Shape::SQSIZE;
        }

        y += Shape::SQSIZE;
        x = INITIAL_XPOS;
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

SShape::SShape()
{
    u_int16_t x = INITIAL_XPOS;
    u_int16_t y = INITIAL_YPOS;
    
    m_matrix[0][0].setFillColor(sf::Color::Magenta);
    m_matrix[0][1].setFillColor(sf::Color::Black);
    m_matrix[0][2].setFillColor(sf::Color::Black);
    m_matrix[1][0].setFillColor(sf::Color::Magenta);
    m_matrix[1][1].setFillColor(sf::Color::Magenta);
    m_matrix[1][2].setFillColor(sf::Color::Black);
    m_matrix[2][0].setFillColor(sf::Color::Black);
    m_matrix[2][1].setFillColor(sf::Color::Magenta);
    m_matrix[2][2].setFillColor(sf::Color::Black);   

    for (u_int8_t i = 0; i < ROWS; ++i)
    {
        for (u_int8_t j = 0; j < COLS; ++j)
        {
            m_matrix[i][j].setOutlineColor(sf::Color::Black);
            m_matrix[i][j].setOutlineThickness(1);
            m_matrix[i][j].setSize(sf::Vector2f(25.0f, 25.0f));
            m_matrix[i][j].setPosition(x, y);
            x += Shape::SQSIZE;
        }

        y += Shape::SQSIZE;
        x = INITIAL_XPOS;
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

TetrisUI::TetrisUI(sf::RenderWindow& window, u_int16_t boardWidth) : 
m_topBorder(sf::Vector2f(boardWidth, 5)), m_window(window), m_boardWidth(boardWidth)
{
    m_font.loadFromFile("arial.ttf");

    m_topBorder.setPosition(0, 50);

    m_yourScoreText.setFont(m_font);
    m_yourScoreText.setCharacterSize(20);
    m_yourScoreText.setString("Your score: ");
    m_yourScoreText.setPosition(240, 10);

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(20);
    m_scoreText.setPosition(350, 10);
    m_scoreText.setString("0");

    m_yourLevelText.setFont(m_font);
    m_yourLevelText.setCharacterSize(20);
    m_yourLevelText.setString("Your level: ");
    m_yourLevelText.setPosition(20, 10);

    m_levelText.setFont(m_font);
    m_levelText.setCharacterSize(20);
    m_levelText.setPosition(120, 10);
    m_levelText.setString("1");
}

void TetrisUI::DisplayScoreAndLevel()
{
    m_window.draw(m_topBorder);
    m_window.draw(m_yourScoreText);
    m_window.draw(m_scoreText);
    m_window.draw(m_yourLevelText);
    m_window.draw(m_levelText);
}

sf::Text& TetrisUI::GetScoreText() { return m_scoreText; }
sf::Text& TetrisUI::GetLevelText() { return m_levelText; }

Board::Board(u_int16_t width, u_int16_t height, std::string title) :
m_window(sf::VideoMode(width, height), title.c_str()), m_currPiece(nullptr)
{
    m_window.setFramerateLimit(50);
}

Board::~Board()
{
    for (Shape *piece : m_staticPieces)
    {
        delete piece;
    }

    if (m_currPiece)
    {
        delete m_currPiece;
    }
}

sf::RenderWindow& Board::GetWindow() { return m_window; }
std::vector<Shape *>& Board::GetShapesContainer() { return m_staticPieces; }
Shape * Board::GetCurrPiece() { return m_currPiece; }
void Board::SetCurrPiece(Shape *shape) { m_currPiece = shape; }

GameEngine::GameEngine(u_int16_t width, u_int16_t height, std::string title, std::string username) :
m_board(width, height, title.c_str()), m_boardWidth(width), m_boardHeight(height),
m_frameTime(200), m_score(0), m_level(1), m_shouldRun(true), m_username(username),
m_shapeOptions({ []()->Shape * { return new LShape; },
[]()->Shape * { return new SquareShape; }, []()->Shape * { return new PlusShape; },
[]()->Shape * { return new LineShape; }, []()->Shape * { return new SShape; }}),
m_UI(m_board.GetWindow(), width) {}

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
                WriteScoreToDB(m_username, std::to_string(m_score));
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
    Shape *shape = m_shapeOptions[GetRandomShape()]();
    m_board.SetCurrPiece(shape);
}

bool GameEngine::IsOnFloor()
{
    Shape *currPiece = m_board.GetCurrPiece();

    if (currPiece)
    {
        for (u_int8_t i = 0; i < Shape::COLS; ++i)
        {
            if (currPiece->GetMatrix()[2][i].getFillColor() != sf::Color::Black && 
                currPiece->GetMatrix()[2][i].getPosition().y == m_boardHeight - Shape::SQSIZE)
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
    Shape *currPiece = m_board.GetCurrPiece();
    std::vector<Shape *>& staticPieces = m_board.GetShapesContainer();

    for (u_int16_t s = 0; s < size; ++s) // runs on all staticPieces
    {
        for (u_int8_t i = Shape::ROWS; i > 0; --i) // runs on currPiece rows
        {
            for (u_int8_t j = 0; j < Shape::COLS; ++j) // runs on currPiece cols
            {
                for (u_int8_t k = 0; k < Shape::ROWS; ++k) // runs on currPiece from staticPieces rows
                {
                    for (u_int8_t p = 0; p < Shape::COLS; ++p) // runs on currPiece from staticPieces cols
                    {
                        if (currPiece->GetMatrix()[i - 1][j].getFillColor() != sf::Color::Black &&
                            staticPieces[s]->GetMatrix()[k][p].getFillColor() != sf::Color::Black &&
                            currPiece->GetMatrix()[i - 1][j].getPosition().x ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().x && 
                            currPiece->GetMatrix()[i - 1][j].getPosition().y + Shape::SQSIZE ==
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
    Shape *currPiece = m_board.GetCurrPiece();
    std::vector<Shape *>& staticPieces = m_board.GetShapesContainer();

    for (u_int16_t s = 0; s < size; ++s) 
    {
        for (u_int8_t i = 0; i < Shape::ROWS; ++i) 
        {
            for (u_int8_t j = 0; j < Shape::COLS; ++j) 
            {
                for (u_int8_t k = 0; k < Shape::ROWS; ++k) 
                {
                    for (u_int8_t p = 0; p < Shape::COLS; ++p) 
                    {
                        if (currPiece->GetMatrix()[i][j].getFillColor() != sf::Color::Black &&
                            staticPieces[s]->GetMatrix()[k][p].getFillColor() != sf::Color::Black &&
                            currPiece->GetMatrix()[i][j].getPosition().y ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().y && 
                            (currPiece->GetMatrix()[i][j].getPosition().x + Shape::SQSIZE ==
                            staticPieces[s]->GetMatrix()[k][p].getPosition().x || 
                            currPiece->GetMatrix()[i][j].getPosition().x - Shape::SQSIZE ==
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
    for (u_int8_t i = 0; i < Shape::ROWS; ++i)
    {
        for (u_int8_t j = 0; j < Shape::COLS; ++j)
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
    for (u_int8_t i = 0; i < Shape::ROWS; ++i)
    {
        for (u_int8_t j = 0; j < Shape::COLS; ++j)
        {
            if (m_board.GetCurrPiece()->GetMatrix()[i][j].getFillColor() != sf::Color::Black && 
                m_board.GetCurrPiece()->GetMatrix()[i][j].getPosition().x == m_boardWidth - Shape::SQSIZE)
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

    for (Shape *piece : m_board.GetShapesContainer())
    {
        piece->Draw(m_board.GetWindow());
    }

    m_UI.DisplayScoreAndLevel();

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
    u_int16_t sum = 0;

    for (u_int16_t s = 0; s < size; ++s)
    {
        for (u_int8_t i = 0; i < Shape::ROWS; ++i)
        {
            for (u_int8_t j = 0; j < Shape::COLS; ++j)
            {
                if (m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getFillColor() != sf::Color::Black)
                {
                    map[m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y] +=
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().x;
                }
            }
        }
    }

    for (u_int16_t i = Shape::SQSIZE; i < m_boardWidth; i += Shape::SQSIZE)
    {
        sum += i;
    }

    for (std::pair<const u_int16_t, u_int16_t> i : map)
    {
        if (i.second == sum)
        {
            fullRowHeight = i.first;
            ++numRowsToErase;

            for (u_int16_t s = 0; s < size; ++s)
            {
                for (u_int8_t j = 0; j < Shape::ROWS; ++j)
                {
                    for (u_int8_t k = 0; k < Shape::COLS; ++k)
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

    m_score += 10*numRowsToErase;
    m_UI.GetScoreText().setString(std::to_string(m_score));
    
    if (m_score >= 50*m_level)
    {
        ++m_level;
        m_frameTime -= 100;
        m_UI.GetLevelText().setString(std::to_string(m_level));
    }

    for (u_int16_t s = 0; s < size; ++s)
    {
        for (u_int8_t i = 0; i < Shape::ROWS; ++i)
        {
            for (u_int8_t j = 0; j < Shape::COLS; ++j)
            {
                if (m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y < fullRowHeight)
                {
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].setPosition(
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().x,
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y + numRowsToErase*Shape::SQSIZE);
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
        for (u_int8_t i = 0; i < Shape::ROWS; ++i)
        {
            for (u_int8_t j = 0; j < Shape::COLS; ++j)
            {
                if (m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getPosition().y == Shape::INITIAL_YPOS &&
                    m_board.GetShapesContainer()[s]->GetMatrix()[i][j].getFillColor() != sf::Color::Black)
                {
                    m_shouldRun = false;
                }
            }
        }
    }
}

void GameEngine::WriteScoreToDB(std::string username, std::string score)
{
    std::string selectQuery = "SELECT score FROM score_table WHERE username = '" + username + "';";
    sqlite3_stmt* selectStmt;
    u_int16_t existingScore = 0;

    sqlite3_open("highscores.db", &m_scoreDB);

    //select the relevant row
    sqlite3_prepare_v2(m_scoreDB, selectQuery.c_str(), -1, &selectStmt, nullptr);

    // if row exists, retrieve the existing score
    if (sqlite3_step(selectStmt) == SQLITE_ROW) 
    {
        existingScore = sqlite3_column_int(selectStmt, 0);
    }

    sqlite3_finalize(selectStmt);

    if (std::stoi(score) > existingScore)
    {
        std::string updateQuery;

        if (existingScore == 0) // if user doesn't exist, insert a new record
        {
            updateQuery = "INSERT INTO score_table (username, score) VALUES ('" + username + "', " + score + ");";
        }

        else
        {
            updateQuery = "UPDATE score_table SET score = " + score + " WHERE username = '" + username + "';";
        }

        sqlite3_exec(m_scoreDB, updateQuery.c_str(), 0, 0, nullptr);
    }

    sqlite3_close(m_scoreDB);
}