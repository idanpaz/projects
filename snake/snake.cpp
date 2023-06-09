#include <random>

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

void Snake::MoveSnake(Dir dir)
{
    u_int16_t xPos = GetSnakeContainer().front().getPosition().x;
    u_int16_t yPos = GetSnakeContainer().front().getPosition().y;
    u_int16_t diameter = m_pointRadius * 2;
    switch (dir)
    {
        case LEFT:
        {
            AddPoint(xPos - diameter, yPos);
            break;
        }

        case RIGHT:
        {
            AddPoint(xPos + diameter, yPos);
            break;
        }

        case UP:
        {
            AddPoint(xPos, yPos - diameter);
            break;
        }

        case DOWN:
        {
            AddPoint(xPos, yPos + diameter);
            break;
        }
    }
}

void Snake::Draw(sf::RenderWindow& window)
{
    for (const sf::CircleShape& point : m_vector)
    {
        window.draw(point);
    }
}

std::vector<sf::CircleShape>& Snake::GetSnakeContainer() { return m_vector; }

Food::Food(u_int16_t radius, u_int16_t width, u_int16_t height) : 
m_radius(radius), m_boardWidth(width), m_boardHeight(height)
{
    m_foodObj.setRadius(radius);
    m_foodObj.setFillColor(sf::Color::Blue);
    m_foodObj.setPosition(GetRandomXPosition(), GetRandomYPosition());
}

void Food::Draw(sf::RenderWindow& window)
{
    window.draw(m_foodObj);
}

sf::CircleShape& Food::GetFoodObj() { return m_foodObj; }

u_int16_t Food::GetRandomXPosition()
{
    std::mt19937 gen(m_rd());
    u_int16_t diameter = m_radius * 2;
    std::uniform_int_distribution<u_int16_t> disX(0, 
    (m_boardWidth - diameter) / diameter);

    return disX(gen) * diameter;
}

u_int16_t Food::GetRandomYPosition()
{
    std::mt19937 gen(m_rd());
    u_int16_t diameter = m_radius * 2;
    std::uniform_int_distribution<u_int16_t> disY(0, 
    (m_boardHeight - diameter) / diameter);

    u_int16_t ret = disY(gen) * diameter;

    if (ret <= 60)
    {
        ret = 60;
    }

    return ret;
}

SnakeUI::SnakeUI(u_int16_t boardWidth) : 
m_topBorder(sf::Vector2f(boardWidth, 5))                                     
{
    m_font.loadFromFile("arial.ttf");

    m_topBorder.setPosition(0, 55);

    m_yourScoreText.setFont(m_font);
    m_yourScoreText.setString("Your score: ");
    m_yourScoreText.setPosition(570, 5);

    m_scoreText.setFont(m_font);
    m_scoreText.setPosition(730, 5);
    m_scoreText.setString("0");

    m_yourLevelText.setFont(m_font);
    m_yourLevelText.setString("Your level: ");
    m_yourLevelText.setPosition(50, 5);

    m_levelText.setFont(m_font);
    m_levelText.setPosition(200, 5);
    m_levelText.setString("1");
}

void SnakeUI::Draw(sf::RenderWindow& window)
{
    window.draw(m_topBorder);
    window.draw(m_yourScoreText);
    window.draw(m_scoreText);
    window.draw(m_yourLevelText);
    window.draw(m_levelText);
}

sf::Text& SnakeUI::GetScoreText() { return m_scoreText; }
sf::Text& SnakeUI::GetLevelText() { return m_levelText; }

Board::Board(u_int16_t width, u_int16_t height, std::string title, 
             u_int16_t initialSnakeSize, u_int16_t pointRadius) : 
             m_window(sf::VideoMode(width, height + 100), title.c_str()),
             m_boardObjects({ new Snake(initialSnakeSize, pointRadius),
                              new Food(pointRadius, width, height),
                              new SnakeUI(width) }) {}

Board::~Board()
{
    for (BoardObjects *boardObject : m_boardObjects)
    {
        delete boardObject;
    }
}

sf::RenderWindow& Board::GetWindow() { return m_window; }

std::vector<BoardObjects *> & Board::GetBoardObjects(){ return m_boardObjects; }

GameEngine::GameEngine(u_int16_t width, u_int16_t height, std::string title, 
                       u_int16_t initialSnakeSize, u_int16_t pointRadius, 
                       std::string username) : 
                       m_board(width, height, title, 
                       initialSnakeSize, pointRadius),
                       m_dir(RIGHT), m_shouldRun(true), m_score(0), 
                       m_level(1), m_frameTime(100), m_username(username) {}

void GameEngine::DisplayBoardObjects()
{
    Snake *snake = static_cast<Snake *>(m_board.GetBoardObjects()[0]);

    m_board.GetWindow().clear();

    for (BoardObjects *boardObject : m_board.GetBoardObjects())
    {
        boardObject->Draw(m_board.GetWindow());
    }

    snake->MoveSnake(m_dir);
    snake->GetSnakeContainer().pop_back();

    m_board.GetWindow().display();
}

void GameEngine::CheckFood()
{
    Snake *snake = static_cast<Snake *>(m_board.GetBoardObjects()[0]);
    Food *food = static_cast<Food *>(m_board.GetBoardObjects()[1]);
    SnakeUI *snakeUI = static_cast<SnakeUI *>(m_board.GetBoardObjects()[2]);

    if (snake->GetSnakeContainer().front().getPosition() ==
        food->GetFoodObj().getPosition())
    {
        u_int16_t xPos = food->GetRandomXPosition();
        u_int16_t yPos = food->GetRandomYPosition();

        for (sf::CircleShape& point : snake->GetSnakeContainer())
        {
            while (point.getPosition().x == xPos && point.getPosition().y == yPos)
            {
                xPos = food->GetRandomXPosition();
                yPos = food->GetRandomYPosition();
            }
        }

        food->GetFoodObj().setPosition(xPos, yPos);
        
        snake->MoveSnake(m_dir);
        ++m_score;
        
        snakeUI->GetScoreText().setString(std::to_string(m_score));

        if (m_score >= m_level*10)
        {
            ++m_level;
            m_frameTime -= 20;
            snakeUI->GetLevelText().setString(std::to_string(m_level));
        }
    }
}

void GameEngine::CheckDeath()
{
    Snake *snake = static_cast<Snake *>(m_board.GetBoardObjects()[0]);
    size_t snakeSize = snake->GetSnakeContainer().size();
    auto frontPos = snake->GetSnakeContainer().front().getPosition();

    if (frontPos.x == m_board.GetWindow().getSize().x || frontPos.x >= 65500 ||
        frontPos.y == m_board.GetWindow().getSize().y || frontPos.y <= 50)
    {
        m_shouldRun = false;
    }

    for (size_t i = 1; i < snakeSize; ++i)
    {
        if (snake->GetSnakeContainer()[i].getPosition() == frontPos)
        {
            m_shouldRun = false;
        }
    }
}

void GameEngine::ChangeDir(sf::Event& event)
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
                ChangeDir(event);          
            }
        }

        if (m_shouldRun && clock.getElapsedTime().asMilliseconds() >= m_frameTime)
        {
            DisplayBoardObjects();
            CheckFood();
            CheckDeath();
            clock.restart();
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