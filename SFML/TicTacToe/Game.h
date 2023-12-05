#pragma once

#include <SFML/Graphics.hpp>

class Game {
    sf::RenderWindow window;

    sf::Font font;
    sf::Text player1Text, player2Text, playAgainText;

    sf::RectangleShape playAgainRect;

    std::vector<int> board;

    std::vector<sf::RectangleShape> squares;

    std::vector<sf::Text> squareTexts;

    bool XToPlay = true, player1IsX = true;

    int player1Score = 0, player2Score = 0;

    sf::Cursor arrowCursor;
    sf::Cursor handCursor;

    void init();

    void render();

    void update();

    void handleMouseMoved(sf::Vector2i mousePos);

    void handleMouseClicked(sf::Vector2i mousePos);

    void handleEvents();

    bool checkWin();

    std::pair<int, int> getOutsideWinningSquares();

    void startNewGame();
public:
    Game();

    void run();
};
