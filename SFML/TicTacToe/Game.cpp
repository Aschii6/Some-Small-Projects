#include "Game.h"

#include <cmath>

std::pair<int, int> Game::getOutsideWinningSquares() {
    for (int i = 0; i < 3; i++) {
        if (board[i * 3] != 0 && board[i * 3] == board[i * 3 + 1] && board[i * 3] == board[i * 3 + 2]) {
            return {i * 3, i * 3 + 2};
        }

        if (board[i] != 0 && board[i] == board[i + 3] && board[i] == board[i + 6]) {
            return {i, i + 6};
        }
    }

    if (board[0] != 0 && board[0] == board[4] && board[0] == board[8]) {
        return {0, 8};
    }

    if (board[2] != 0 && board[2] == board[4] && board[2] == board[6]) {
        return {2, 6};
    }

    return {-1, -1};
}

void Game::startNewGame() {
    player1IsX = !player1IsX;

    XToPlay = true;

    std::string s1 = "Player 1\nNow plays with ";
    std::string s2 = "Player 2\nNow plays with ";

    if (player1IsX) {
        s1 += std::string("X\n");
        s2 += std::string("O\n");
    } else {
        s2 += std::string("X\n");
        s1 += std::string("O\n");
    }

    s1 += "Current wins: " + std::to_string(player1Score);
    s2 += "Current wins: " + std::to_string(player2Score);

    player1Text.setString(s1);

    player2Text.setString(s2);

    for (int i = 0; i < 9; i++) {
        board[i] = 0;
    }

    for (int i = 0; i < 9; i++) {
        squareTexts[i].setString("");
    }
}

Game::Game() {
    init();
}

void Game::render() {
    window.clear(sf::Color::White);

    window.draw(player1Text);

    for (const auto& square : squares)
        window.draw(square);

    for (const auto& text : squareTexts)
        window.draw(text);

    window.draw(player1Text);
    window.draw(player2Text);

    if (checkWin()) {
        window.draw(playAgainRect);
        window.draw(playAgainText);

        auto [fst, snd] = getOutsideWinningSquares();

        if (fst != -1 && snd != -1) {
            sf::Vector2f startPos = squares[fst].getGlobalBounds().getPosition() +
                                    squares[fst].getGlobalBounds().getSize() / 2.f;

            sf::Vector2f endPos = squares[snd].getGlobalBounds().getPosition() +
                                  squares[snd].getGlobalBounds().getSize() / 2.f;

            sf::Vector2f direction = endPos - startPos;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            sf::RectangleShape line(sf::Vector2f(length, 7));
            line.setPosition(startPos);
            line.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159265f);
            line.setFillColor(sf::Color::Red);

            window.draw(line);
        }
    }

    window.display();
}

void Game::update() {
    handleEvents();

    render();
}

void Game::handleMouseMoved(sf::Vector2i mousePos) {
    bool cursorShouldBecomeHand = false;

    sf::Vector2f mousePosFloat = sf::Vector2f(static_cast<float> (mousePos.x), static_cast<float> (mousePos.y));

    for (const auto& sq : squares) {
        if (sq.getGlobalBounds().contains(mousePosFloat)) {
            cursorShouldBecomeHand = true;
            break;
        }
    }

    if (cursorShouldBecomeHand)
        window.setMouseCursor(handCursor);
    else
        window.setMouseCursor(arrowCursor);
}

void Game::handleMouseClicked(sf::Vector2i mousePos) {
    sf::Vector2f mousePosFloat = sf::Vector2f(static_cast<float> (mousePos.x), static_cast<float> (mousePos.y));

    if (checkWin()) {
        if (playAgainRect.getGlobalBounds().contains(mousePosFloat)) {
            startNewGame();
        }
        return;
    }

    for (int i = 0; i < squares.size(); i++) {
        if (squares[i].getGlobalBounds().contains(mousePosFloat)) {
            if (board[i] == 0) {
                if (XToPlay) {
                    board[i] = 1;
                    squareTexts[i].setString("X");
                }
                else {
                    board[i] = 2;
                    squareTexts[i].setString("O");
                }
                if (checkWin()) {
                    if (player1IsX) {
                        if (XToPlay)
                            player1Score++;
                        else
                            player2Score++;
                    }
                    else {
                        if (XToPlay)
                            player2Score++;
                        else
                            player1Score++;
                    }
                }
                XToPlay = !XToPlay;
            }
            break;
        }
    }
}

void Game::handleEvents() {
    sf::Event event{};

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseMoved) {
            handleMouseMoved(sf::Mouse::getPosition(window));
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            handleMouseClicked(sf::Mouse::getPosition(window));
        }
    }
}

bool Game::checkWin() {
    return getOutsideWinningSquares() != std::pair<int, int>(-1, -1);
}

void Game::init() {
    window.create(sf::VideoMode(600, 800), "TicTacToe");

    font.loadFromFile("../Resources/arial_bold.ttf");
    player1Text.setFont(font);
    player2Text.setFont(font);

    player1Text.setFillColor(sf::Color::Black);
    player1Text.setCharacterSize(24);
    player1Text.setPosition(10, 10);

    player2Text.setFillColor(sf::Color::Black);
    player2Text.setCharacterSize(24);
    player2Text.setPosition(350, 10);

    for (int i = 0; i < 9; i++) {
        board.push_back(0);

        sf::RectangleShape shape(sf::Vector2f(150, 150));

        int x = 75 + i / 3 * 150;
        int y = 300 + i % 3 * 150;

        shape.setPosition(static_cast<float> (x), static_cast<float> (y));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(5);

        squares.push_back(shape);

        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(60);

        sf::FloatRect bound = squares[i].getGlobalBounds();

        text.setPosition(bound.left + bound.width / 2 - 25, bound.top + bound.height / 2 - 35);

        squareTexts.push_back(text);
    }

    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);

    std::string s1 = "Player 1\nNow plays with ";
    std::string s2 = "Player 2\nNow plays with ";

    s1 += std::string("X\n");
    s2 += std::string("O\n");

    s1 += "Current wins: " + std::to_string(player1Score);
    s2 += "Current wins: " + std::to_string(player2Score);

    player1Text.setString(s1);
    player2Text.setString(s2);

    playAgainRect = sf::RectangleShape(sf::Vector2f(300, 100));
    playAgainRect.setOutlineColor(sf::Color::Black);
    playAgainRect.setOutlineThickness(5);

    playAgainRect.setPosition(150, 150);


    playAgainText.setFont(font);
    playAgainText.setFillColor(sf::Color::Black);
    playAgainText.setCharacterSize(24);

    sf::FloatRect bound = playAgainRect.getGlobalBounds();

    playAgainText.setString("Play again?");
    playAgainText.setPosition(bound.left + bound.width / 2 - playAgainText.getGlobalBounds().width / 2,
        bound.top + bound.height / 2 - playAgainText.getGlobalBounds().height / 2);
}

void Game::run() {
    while (window.isOpen())
        update();
}

