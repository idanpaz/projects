#include <SFML/Graphics.hpp>
#include <sqlite3.h>
#include <sys/types.h>
#include <vector>
#include <memory>
#include <functional>
#include <random>

class IShape
{
public:
    static const u_int8_t SQSIZE = 25;
    virtual ~IShape();
    virtual void RotateLeft() = 0;

    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void Draw(sf::RenderWindow& window);
    sf::RectangleShape (&GetMatrix())[3][3];

protected:
    IShape();

    sf::RectangleShape m_matrix[3][3];
    u_int16_t m_currOrrientation;
};

class LShape : public IShape
{
public:
    explicit LShape();
    void RotateLeft() override;
};

class SquareShape : public IShape
{
public:
    explicit SquareShape();
    void RotateLeft() override;
};

class PlusShape : public IShape
{
public:
    explicit PlusShape();
    void RotateLeft() override;
};

class LineShape : public IShape
{
public:
    explicit LineShape();
    void RotateLeft() override;
};

class SShape : public IShape
{
public:
    explicit SShape();
    void RotateLeft() override;
};

class TetrisUI
{
public:
    TetrisUI(sf::RenderWindow& window, u_int16_t boardWidth);

    void DisplayScoreAndLevel();
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
    sf::RenderWindow& m_window;
};

class Board
{
public:
    explicit Board(u_int16_t width, u_int16_t height, std::string title);
    ~Board();

    sf::RenderWindow& GetWindow();
    std::vector<IShape *>& GetShapesContainer();
    IShape *GetCurrPiece();

    void SetCurrPiece(IShape *shape);

private:
    sf::RenderWindow m_window;
    std::vector<IShape *> m_staticPieces;
    IShape *m_currPiece;
};

class GameEngine
{
public:
    explicit GameEngine(u_int16_t width, u_int16_t height, 
                        std::string title, std::string username);

    void Run();

private:
    void HandleInputs(sf::Event& event);
    void GenerateNewPiece();
    void DisplayBoardPieces();
    void DrawAllPieces();
    void ScanRows();
    void CheckDeath();
    bool IsOnOtherPiece();
    bool IsOnFloor();
    bool IsAsideOtherPiece();
    bool IsOnLeftEdge();
    bool IsOnRightEdge();
    u_int16_t GetRandomShape();
    void WriteScoreToDB(std::string username, std::string score);

    Board m_board;
    u_int16_t m_boardWidth;
    u_int16_t m_boardHeight;
    u_int16_t m_frameTime;
    u_int16_t m_score;
    u_int16_t m_level;
    std::string m_username;
    std::vector<std::function<IShape *()> > m_shapeOptions;
    std::random_device m_rd;
    bool m_shouldRun;
    TetrisUI m_UI;
    sqlite3* m_scoreDB;
};