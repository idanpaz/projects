#include <iostream>

#include "snake.hpp"

std::vector<std::pair<std::string, int>> GetTopScores()
{
    std::vector<std::pair<std::string, int>> scores;

    sqlite3* db;
    int rc = sqlite3_open("highscores.db", &db);

    if (rc)
    {
        std::cerr << "Cannot open the database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return scores;
    }

    std::string sqlCommand = "SELECT username, score FROM score_table ORDER BY cast(score AS INTEGER) DESC LIMIT 10;";

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sqlCommand.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to execute SQL query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return scores;
    }

    int position = 1;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string username(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        int score = sqlite3_column_int(stmt, 1);
        scores.push_back(std::make_pair(std::to_string(position) + ". " + username, score));
        ++position;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return scores;
}

int main()
{
    sf::RenderWindow gameConsole(sf::VideoMode(800, 600), "Game Console");
    sf::Font font;
    sf::Text welcome("Welcome to Snake!", font, 40);
    sf::Text userName("Enter your username: ", font, 20);
    sf::Event event;
    sf::RectangleShape nameInput(sf::Vector2f(200, 30));
    std::string nickName("");
    sf::Text nick("", font, 20);
    sf::RectangleShape startButton(sf::Vector2f(300, 100));
    sf::Text startGame("Start Game", font, 50);
    sf::RectangleShape highScores(sf::Vector2f(300, 100));
    sf::Text highScoresText("High Scores", font, 50);

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "couldn't load font\n";
    }
    
    welcome.setPosition(200, 10);
    userName.setPosition(150, 80);
    nameInput.setPosition(400, 80);
    nick.setPosition(400, 80);
    nick.setFillColor(sf::Color::Red);
    startButton.setOutlineColor(sf::Color::Red);
    startButton.setOutlineThickness(5);
    startButton.setPosition(250, 200);
    startGame.setPosition(270, 220);
    startGame.setFillColor(sf::Color::Red);
    highScores.setOutlineColor(sf::Color::Red);
    highScores.setOutlineThickness(5);
    highScores.setPosition(250, 400);
    highScoresText.setPosition(265, 420);
    highScoresText.setFillColor(sf::Color::Red);

    while (gameConsole.isOpen())
    {
        while (gameConsole.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) gameConsole.close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == '\b' && !nickName.empty()) nickName.pop_back();

                    else if (event.text.unicode != '\b') nickName += static_cast<char>(event.text.unicode);

                    nick.setString(nickName);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(gameConsole);

                    if (startGame.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        GameEngine snake(800, 600, "Snake Game", 5, 10, nickName);
                        snake.Run();
                    }

                    else if (highScores.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        std::vector<std::pair<std::string, int>> topScores = GetTopScores();
                        
                        sf::RenderWindow topScoresWindow(sf::VideoMode(400, 300), "Top Scores");
                        sf::Text scoresText("", font, 20);
                        scoresText.setPosition(20, 20);
                        std::string scoresString;

                        for (const auto& score : topScores)
                        {
                            scoresString += score.first + ": " + std::to_string(score.second) + "\n";
                        }

                        scoresText.setString(scoresString);

                        while (topScoresWindow.isOpen())
                        {
                            sf::Event topScoresEvent;

                            while (topScoresWindow.pollEvent(topScoresEvent))
                            {
                                if (topScoresEvent.type == sf::Event::Closed)
                                    topScoresWindow.close();
                            }

                            topScoresWindow.clear();
                            topScoresWindow.draw(scoresText);
                            topScoresWindow.display();
                        }
                    }
                }
            }

            gameConsole.clear();

            gameConsole.draw(welcome);
            gameConsole.draw(userName);
            gameConsole.draw(nameInput);
            gameConsole.draw(nick);
            gameConsole.draw(startButton);
            gameConsole.draw(startGame);
            gameConsole.draw(highScores);
            gameConsole.draw(highScoresText);

            gameConsole.display();       
        }
    }

    return 0;
}