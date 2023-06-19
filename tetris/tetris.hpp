#include <SFML/Graphics.hpp>
#include <sys/types.h>
#include <vector>
#include <memory>
#include <functional>
#include <random>

class IShape
{
public:
    virtual ~IShape() {}
    virtual void Draw(sf::RenderWindow& window) = 0;

    virtual void RotateLeft() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;
    virtual void MoveDown() = 0;
    virtual sf::RectangleShape (&GetMatrix())[3][3] = 0;
};

class LShape : public IShape
{
public:
    explicit LShape();
    void Draw(sf::RenderWindow& window);

    void RotateLeft() override;
    void MoveLeft() override;
    void MoveRight() override;
    void MoveDown() override;

    sf::RectangleShape (&GetMatrix())[3][3] { return m_matrix; }

private:
    sf::RectangleShape m_matrix[3][3];
    u_int16_t m_currOrrientation;
};

class SquareShape : public IShape
{
public:
    explicit SquareShape();
    void Draw(sf::RenderWindow& window);

    void RotateLeft() override;
    void MoveLeft() override;
    void MoveRight() override;
    void MoveDown() override;

    sf::RectangleShape (&GetMatrix())[3][3] { return m_matrix; }

private:
    sf::RectangleShape m_matrix[3][3];
};

class PlusShape : public IShape
{
public:
    explicit PlusShape();
    void Draw(sf::RenderWindow& window);

    void RotateLeft() override;
    void MoveLeft() override;
    void MoveRight() override;
    void MoveDown() override;

    sf::RectangleShape (&GetMatrix())[3][3] { return m_matrix; }

private:
    sf::RectangleShape m_matrix[3][3];
    u_int16_t m_currOrrientation;
};

class LineShape : public IShape
{
public:
    explicit LineShape();
    void Draw(sf::RenderWindow& window);

    void RotateLeft() override;
    void MoveLeft() override;
    void MoveRight() override;
    void MoveDown() override;

    sf::RectangleShape (&GetMatrix())[3][3] { return m_matrix; }

private:
    sf::RectangleShape m_matrix[3][3];
    u_int16_t m_currOrrientation;
};

class SShape : public IShape
{
public:
    explicit SShape();
    void Draw(sf::RenderWindow& window);

    void RotateLeft() override;
    void MoveLeft() override;
    void MoveRight() override;
    void MoveDown() override;

    sf::RectangleShape (&GetMatrix())[3][3] { return m_matrix; }

private:
    sf::RectangleShape m_matrix[3][3];
    u_int16_t m_currOrrientation;
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
    explicit GameEngine(u_int16_t width, u_int16_t height, std::string title);

    void Run();

private:
    void HandleInputs(sf::Event& event);
    void GenerateNewPiece();
    void DisplayBoardPieces();
    bool IsOnOtherPiece();
    bool IsOnFloor();
    bool IsAsideOtherPiece();
    bool IsOnLeftEdge();
    bool IsOnRightEdge();
    void DrawAllPieces();
    void ScanRows();
    u_int16_t GetRandomShape();

    Board m_board;
    u_int16_t m_boardWidth;
    u_int16_t m_boardHeight;
    u_int16_t m_frameTime;
    std::vector<std::function<IShape *()> > m_shapeOptions;
    std::random_device m_rd;
};